//
// Created by Johny Georges on 2023-12-31.
//

#include "lexical-analyzer.h"
#include "../../../shared/types/basic-character-type.h"
#include "../../symbol/symbol-factory.h"
#include "../../../shared/utils/logger/logger.h"

LexicalAnalyzer::LexicalAnalyzer(std::shared_ptr<TokenTable> tokenTable, std::shared_ptr<ReservedKeywords> reservedKeywords) {
    _fileReader = FileReader();
    _reservedKeywords = reservedKeywords;
    _charTable = CharTable();
    _tokenTable = tokenTable;
    _hasMore = false;
    _tokenValueIdCursor = INT_MIN;
    _prevToken = std::optional<std::shared_ptr<Token>>();
}

void LexicalAnalyzer::start(std::string &filePath) {
    try {
        _fileReader.open(filePath);
        if (_fileReader.peek()) {
            _hasMore = true;
            _prevToken.reset();
        }
    } catch (std::exception &error) {
        throw error;
    }
}

void LexicalAnalyzer::stop() {
    if (_fileReader.isOpen()) {
        _hasMore = false;
        _prevToken.reset();
        _fileReader.close();
    }
}


std::optional<std::shared_ptr<Lexeme>> LexicalAnalyzer::next() {
    if (!_fileReader.isOpen() || !_hasMore) {
        return {};
    }

    this->skipComments();
    this->stopIfNecessary();
    if (!_hasMore) {
        return {};
    }
    auto line = _fileReader.getPeekLine();
    auto column = _fileReader.getPeekColumn();
    auto nextToken = this->buildNextToken();
    _prevToken = nextToken;
    if (nextToken) {
        auto endLine = _fileReader.getCursor().line;
        auto endColumn = _fileReader.getCursor().column;
        auto lexeme = std::make_shared<Lexeme>(nextToken.value(), line, column, endLine, endColumn);
        return lexeme;
    }
    return {};
}

std::optional<std::shared_ptr<Lexeme>> LexicalAnalyzer::peek() {
    if (!_fileReader.isOpen() || !_hasMore) {
        return {};
    }
    auto cursorSnapshot = _fileReader.getCursor();
    auto numAdvancesSnapshot = _fileReader.getNumAdvances();

    this->skipComments();
    this->stopIfNecessary();
    if (!_hasMore) {
        this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
        return {};
    }
    auto line = _fileReader.getPeekLine();
    auto column = _fileReader.getPeekColumn();
    auto nextToken = this->peekNextToken();
    if (nextToken) {
        auto endLine = _fileReader.getCursor().line;
        auto endColumn = _fileReader.getCursor().column;
        this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
        return std::make_shared<Lexeme>(nextToken.value(), line, column, endLine, endColumn);
    }
    this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
    return {};
}

bool LexicalAnalyzer::hasMore() {
    return _hasMore;
}

std::optional<std::shared_ptr<Token>> LexicalAnalyzer::buildNextToken() {
    auto character = _fileReader.advance();
    if (!character) {
        return {};
    }

    if (isdigit(character.value())) {
        std::string term;
        term += character.value();
        auto isPrevTokenPeriod = (_prevToken && _prevToken.value()->getSymbol()->isPeriod());
        auto isFloat = false;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            if (peekNextChar.value() == PERIOD) {
                if (isPrevTokenPeriod) {
                    break;
                } else if (isFloat) {
                    return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
                } else {
                    isFloat = true;
                }
            }  else if (!isdigit(peekNextChar.value())) {
                break;
            }
            term += peekNextChar.value();
            _fileReader.advance();
            peekNextChar = _fileReader.peek();
        }


        auto valueId = this->generateTokenValueId();
        if (isFloat) {
            _tokenTable->setFloat(valueId, term);
            return std::make_shared<Token>(SymbolFactory::createFloatSymbol(), term, valueId);
        } else {
            _tokenTable->setInt(valueId, term);
            return std::make_shared<Token>(SymbolFactory::createIntSymbol(), term, valueId);
        }

    }

    if (character.value() == SINGLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == SINGLE_QUOTE) {
                auto c = _charTable.match(term);
                if (!c) {
                    return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
                }
                auto valueId = this->generateTokenValueId();
                _tokenTable->setChar(valueId, c.value());
                return std::make_shared<Token>(SymbolFactory::createCharSymbol(), term, valueId);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
    }

    if (character.value() == DOUBLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == DOUBLE_QUOTE) {
                auto valueId = this->generateTokenValueId();
                _tokenTable->setString(valueId, term);
                return std::make_shared<Token>(SymbolFactory::createStringSymbol(), term, valueId);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
    }

    auto isCharacterReservedKeyword = _reservedKeywords->match(character);
    if (isCharacterReservedKeyword) {
        auto reservedKeyword = isCharacterReservedKeyword.value();
        auto nextChar = _fileReader.peek();
        if (nextChar && reservedKeyword->isBang()) {
                std::string term;
                term += character.value();
                term += nextChar.value();
                auto isBangEqual = _reservedKeywords->match(term);
                if (isBangEqual) {
                    _fileReader.advance();
                    return std::make_shared<Token>(isBangEqual.value());
                }
                return std::make_shared<Token>(isCharacterReservedKeyword.value());

        } else if (nextChar && reservedKeyword->isPlus()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isConcatOperator = _reservedKeywords->match(term);
            if (isConcatOperator) {
                _fileReader.advance();
                return std::make_shared<Token>(isConcatOperator.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        } else if (nextChar && reservedKeyword->isStar()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isColonEqual = _reservedKeywords->match(term);
            if (isColonEqual) {
                _fileReader.advance();
                return std::make_shared<Token>(isColonEqual.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        } else if (nextChar &&
                    (reservedKeyword->isEqual() ||
                     reservedKeyword->isGreaterThan() ||
                     reservedKeyword->isLessThan())
                     ) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isEqualityOperator = _reservedKeywords->match(term);
            if (isEqualityOperator) {
                _fileReader.advance();
                return std::make_shared<Token>(isEqualityOperator.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        } else if (nextChar &&
                    (reservedKeyword->isColon())
                ) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isColonColon = _reservedKeywords->match(term);
            if (isColonColon) {
                _fileReader.advance();
                return std::make_shared<Token>(isColonColon.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        }  else if (nextChar && reservedKeyword->isPeriod()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isDotDot = _reservedKeywords->match(term);
            if (isDotDot) {
                _fileReader.advance();
                auto afterNextChar = _fileReader.peek();
                if (afterNextChar) {
                    term += afterNextChar.value();
                    auto isDotDotDot = _reservedKeywords->match(term);
                    if (isDotDotDot) {
                        _fileReader.advance();
                        return std::make_shared<Token>(isDotDotDot.value());
                    }
                }
                return std::make_shared<Token>(isDotDot.value());
            }
        }
        return std::make_shared<Token>(isCharacterReservedKeyword.value());
    }

    std::string term;
    term += character.value();
    auto nextChar = _fileReader.peek();
    while (nextChar) {
        if (nextChar.value() == WHITE_SPACE || nextChar.value() == NEW_LINE || _reservedKeywords->match(nextChar)) {
            auto matchedKeyword = _reservedKeywords->match(term);
            if (matchedKeyword) {
                return std::make_shared<Token>(matchedKeyword.value(), term);
            }
            auto valueId = this->generateTokenValueId();
            _tokenTable->setIdentifier(valueId, term);
            return std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), term, valueId);
        }
        auto c = _fileReader.advance().value();
        term += c;
        nextChar = _fileReader.peek();
    }

    return {};
}

std::optional<std::shared_ptr<Token>> LexicalAnalyzer::peekNextToken() {
    auto character = _fileReader.advance();
    if (!character) {
        return {};
    }
    if (isdigit(character.value())) {
        std::string term;
        term += character.value();
        auto isPrevTokenPeriod = (_prevToken && _prevToken.value()->getSymbol()->isPeriod());
        auto isFloat = false;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            if (peekNextChar.value() == PERIOD) {
                if (isPrevTokenPeriod) {
                    break;
                } else if (isFloat) {
                    return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
                } else {
                    isFloat = true;
                }
            }  else if (!isdigit(peekNextChar.value())) {
                break;
            }
            term += peekNextChar.value();
            _fileReader.advance();
            peekNextChar = _fileReader.peek();
        }

        if (_prevToken && _prevToken.value()->getSymbol()->isPeriod()) {
            isFloat = false;
        }

        if (isFloat) {
            return std::make_shared<Token>(SymbolFactory::createFloatSymbol(), term);
        } else {
            return std::make_shared<Token>(SymbolFactory::createIntSymbol(), term);
        }

    }

    if (character.value() == SINGLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == SINGLE_QUOTE) {
                auto c = _charTable.match(term);
                if (!c) {
                    return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
                }
                return std::make_shared<Token>(SymbolFactory::createCharSymbol(), term);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
    }

    if (character.value() == DOUBLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == DOUBLE_QUOTE) {
                return std::make_shared<Token>(SymbolFactory::createStringSymbol(), term);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return std::make_shared<Token>(SymbolFactory::createMalformedSymbol(term), term);
    }

    auto isCharacterReservedKeyword = _reservedKeywords->match(character);
    if (isCharacterReservedKeyword) {
        auto reservedKeyword = isCharacterReservedKeyword.value();
        auto nextChar = _fileReader.peek();
        if (nextChar && reservedKeyword->isBang()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isBangEqual = _reservedKeywords->match(term);
            if (isBangEqual) {
                _fileReader.advance();
                return std::make_shared<Token>(isBangEqual.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());

        }  else if (nextChar && reservedKeyword->isPlus()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isConcatOperator = _reservedKeywords->match(term);
            if (isConcatOperator) {
                _fileReader.advance();
                return std::make_shared<Token>(isConcatOperator.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        } else if (nextChar && reservedKeyword->isStar()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isColonEqual = _reservedKeywords->match(term);
            if (isColonEqual) {
                _fileReader.advance();
                return std::make_shared<Token>(isColonEqual.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        } else if (nextChar &&
                   (reservedKeyword->isEqual() ||
                    reservedKeyword->isGreaterThan() ||
                    reservedKeyword->isLessThan())
                ) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isEqualityOperator = _reservedKeywords->match(term);
            if (isEqualityOperator) {
                _fileReader.advance();
                return std::make_shared<Token>(isEqualityOperator.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        }  else if (nextChar &&
                    (reservedKeyword->isColon())
                ) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isColonColon = _reservedKeywords->match(term);
            if (isColonColon) {
                _fileReader.advance();
                return std::make_shared<Token>(isColonColon.value());
            }
            return std::make_shared<Token>(isCharacterReservedKeyword.value());
        }  else if (nextChar && reservedKeyword->isPeriod()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isDotDot = _reservedKeywords->match(term);
            if (isDotDot) {
                _fileReader.advance();
                auto afterNextChar = _fileReader.peek();
                if (afterNextChar) {
                    term += afterNextChar.value();
                    auto isDotDotDot = _reservedKeywords->match(term);
                    if (isDotDotDot) {
                        _fileReader.advance();
                        return std::make_shared<Token>(isDotDotDot.value());
                    }
                }
                return std::make_shared<Token>(isDotDot.value());
            }
        }
        return std::make_shared<Token>(isCharacterReservedKeyword.value());
    }

    std::string term;
    term += character.value();
    auto nextChar = _fileReader.peek();
    while (nextChar) {
        if (nextChar.value() == WHITE_SPACE || nextChar.value() == NEW_LINE || _reservedKeywords->match(nextChar)) {
            auto matchedKeyword = _reservedKeywords->match(term);
            if (matchedKeyword) {
                return std::make_shared<Token>(matchedKeyword.value(), term);
            }
            auto valueId = this->generateTokenValueId();
            _tokenTable->setIdentifier(valueId, term);
            return std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), term, valueId);
        }
        auto c = _fileReader.advance().value();
        term += c;
        nextChar = _fileReader.peek();
    }

    return {};
}

void LexicalAnalyzer::skipWhitespaceAndNewLine() {
    auto c = _fileReader.peek();
    if (!c) {
        return;
    }
    while (c == WHITE_SPACE || c == NEW_LINE) {
        _fileReader.advance();
        c = _fileReader.peek();
    }
}

void LexicalAnalyzer::skipComments() {
    this->skipWhitespaceAndNewLine();
    if (_fileReader.peek() != SLASH) {
        return;
    }

    auto cursorSnapshot = _fileReader.getCursor();
    auto numAdvancesSnapshot = _fileReader.getNumAdvances();
    _fileReader.advance();

    if (_fileReader.peek() != SLASH) {
        this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
        return;
    }

    _fileReader.advance();
    auto nextChar = _fileReader.peek();
    while (nextChar.has_value() && nextChar != NEW_LINE) {
        _fileReader.advance();
        nextChar = _fileReader.peek();
    }
    _fileReader.advance();
    this->skipComments();
}

void LexicalAnalyzer::stopIfNecessary() {
    if (!_fileReader.peek()) {
        Logger::log("peek return NOTHING...stopping");
        stop();
    }
}

int LexicalAnalyzer::generateTokenValueId() {
     _tokenValueIdCursor++;
    return _tokenValueIdCursor;
}

void LexicalAnalyzer::resetAfterPeek(Cursor cursor, int numAdvances) {
    _fileReader.setCursor(cursor);
    auto numRetreats = _fileReader.getNumAdvances() - numAdvances;
    for (unsigned long i = 0; i < numRetreats; ++i) {
        _fileReader.retreat();
    }
}
//
// Created by Johny Georges on 2023-12-31.
//

#include "lexical-analyzer.h"
#include "../../../shared/types/basic-character-type.h"
#include "../../symbol/symbol-factory.h"
#include "../../../shared/utils/logger/logger.h"

LexicalAnalyzer::LexicalAnalyzer(TokenTable* tokenTable) {
    _fileReader = FileReader();
    _reservedKeywords = ReservedKeywords();
    _charTable = CharTable();
    _tokenTable = tokenTable;
    _hasMore = false;
    _tokenValueIdCursor = INT_MIN;
}

void LexicalAnalyzer::start(std::string &filePath) {
    try {
        _fileReader.open(filePath);
        if (_fileReader.peek()) {
            _hasMore = true;
        }
    } catch (std::exception &error) {
        throw error;
    }

}

void LexicalAnalyzer::stop() {
    if (_fileReader.isOpen()) {
        _hasMore = false;
        _fileReader.close();
    }
}


std::optional<Lexeme> LexicalAnalyzer::next() {
    if (!_fileReader.isOpen() || !_hasMore) {
        return {};
    }

    this->skipWhitespaceAndNewLine();
    this->stopIfNecessary();
    if (!_hasMore) {
        return {};
    }
    auto line = _fileReader.getPeekLine();
    auto position = _fileReader.getPeekPosition();
    auto nextToken = this->buildNextToken();
    if (nextToken) {
        return Lexeme(nextToken.value(), line, position);
    }
    return {};
}

std::optional<Lexeme> LexicalAnalyzer::peek() {
    if (!_fileReader.isOpen() || !_hasMore) {
        return {};
    }
    auto cursorSnapshot = _fileReader.getCursor();
    auto numAdvancesSnapshot = _fileReader.getNumAdvances();

    this->skipWhitespaceAndNewLine();
    this->stopIfNecessary();
    if (!_hasMore) {
        this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
        return {};
    }
    auto line = _fileReader.getPeekLine();
    auto position = _fileReader.getPeekPosition();
    auto nextToken = this->peekNextToken();
    this->resetAfterPeek(cursorSnapshot, numAdvancesSnapshot);
    if (nextToken) {
        return Lexeme(nextToken.value(), line, position);
    }
    return {};
}

std::optional<Token*> LexicalAnalyzer::buildNextToken() {
    auto character = _fileReader.advance();
    if (!character) {
        return {};
    }

    if (isdigit(character.value())) {
        std::string term;
        term += character.value();
        auto isFloat = false;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            if (peekNextChar.value() == PERIOD && isFloat) {
                return new Token(SymbolFactory::createMalformedSymbol());
            } else if (peekNextChar.value() == PERIOD) {
                isFloat = true;
            } else if (!isdigit(peekNextChar.value())) {
                break;
            }
            term += peekNextChar.value();
            _fileReader.advance();
            peekNextChar = _fileReader.peek();
        }

        auto valueId = this->generateTokenValueId();
        if (isFloat) {
            _tokenTable->setFloat(valueId, std::stof(term));
            return new Token(SymbolFactory::createFloatSymbol(), valueId);
        } else {
            _tokenTable->setInt(valueId, std::stoi(term));
            return new Token(SymbolFactory::createIntSymbol(), valueId);
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
                    return new Token(SymbolFactory::createMalformedSymbol());
                }
                auto valueId = this->generateTokenValueId();
                _tokenTable->setChar(valueId, c.value());
                return new Token(SymbolFactory::createCharSymbol(), valueId);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return new Token(SymbolFactory::createMalformedSymbol());
    }

    if (character.value() == DOUBLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == DOUBLE_QUOTE) {
                auto valueId = this->generateTokenValueId();
                _tokenTable->setString(valueId, term);
                return new Token(SymbolFactory::createStringSymbol(), valueId);
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return new Token(SymbolFactory::createMalformedSymbol());
    }

    auto isCharacterReservedKeyword = _reservedKeywords.match(character);
    if (isCharacterReservedKeyword) {
        auto reservedKeyword = isCharacterReservedKeyword.value();
        auto nextChar = _fileReader.peek();
        if (nextChar && reservedKeyword->isBang()) {
                std::string term;
                term += character.value();
                term += nextChar.value();
                auto isBangEqual = _reservedKeywords.match(term);
                if (isBangEqual) {
                    _fileReader.advance();
                    return new Token(isBangEqual.value());
                }
                return new Token(isCharacterReservedKeyword.value());

        } else if (nextChar && reservedKeyword->isEqual()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isEqualEqual = _reservedKeywords.match(term);
            if (isEqualEqual) {
                _fileReader.advance();
                return new Token(isEqualEqual.value());
            }
            return new Token(isCharacterReservedKeyword.value());

        } else {
            return new Token(isCharacterReservedKeyword.value());
        }
    }

    std::string term;
    term += character.value();
    auto nextChar = _fileReader.peek();
    while (nextChar) {
        if (nextChar.value() == WHITE_SPACE || nextChar.value() == NEW_LINE || _reservedKeywords.match(nextChar)) {
            return new Token(
                    _reservedKeywords.match(term)
                    .value_or(SymbolFactory::createIdentifierSymbol())
                    );
        }
        auto c = _fileReader.advance().value();
        term += c;
        nextChar = _fileReader.peek();
    }

    return {};
}

std::optional<Token*> LexicalAnalyzer::peekNextToken() {
    auto character = _fileReader.advance();
    if (!character) {
        return {};
    }

    if (isdigit(character.value())) {
        std::string term;
        term += character.value();
        auto isFloat = false;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            if (peekNextChar.value() == PERIOD && isFloat) {
                return new Token(SymbolFactory::createMalformedSymbol());
            } else if (peekNextChar.value() == PERIOD) {
                isFloat = true;
            } else if (!isdigit(peekNextChar.value())) {
                break;
            }
            term += peekNextChar.value();
            _fileReader.advance();
            peekNextChar = _fileReader.peek();
        }

        if (isFloat) {
            return new Token(SymbolFactory::createFloatSymbol());
        } else {
            return new Token(SymbolFactory::createIntSymbol());
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
                    return new Token(SymbolFactory::createMalformedSymbol());
                }
                return new Token(SymbolFactory::createCharSymbol());
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return new Token(SymbolFactory::createMalformedSymbol());
    }

    if (character.value() == DOUBLE_QUOTE) {
        std::string term;
        auto peekNextChar = _fileReader.peek();
        while (peekNextChar) {
            auto nextChar = _fileReader.advance();
            if (nextChar.value() == DOUBLE_QUOTE) {
                return new Token(SymbolFactory::createStringSymbol());
            }
            term += nextChar.value();
            peekNextChar = _fileReader.peek();
        }
        return new Token(SymbolFactory::createMalformedSymbol());
    }

    auto isCharacterReservedKeyword = _reservedKeywords.match(character);
    if (isCharacterReservedKeyword) {
        auto reservedKeyword = isCharacterReservedKeyword.value();
        auto nextChar = _fileReader.peek();
        if (nextChar && reservedKeyword->isBang()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isBangEqual = _reservedKeywords.match(term);
            if (isBangEqual) {
                _fileReader.advance();
                return new Token(isBangEqual.value());
            }
            return new Token(isCharacterReservedKeyword.value());

        } else if (nextChar && reservedKeyword->isEqual()) {
            std::string term;
            term += character.value();
            term += nextChar.value();
            auto isEqualEqual = _reservedKeywords.match(term);
            if (isEqualEqual) {
                _fileReader.advance();
                return new Token(isEqualEqual.value());
            }
            return new Token(isCharacterReservedKeyword.value());

        } else {
            return new Token(isCharacterReservedKeyword.value());
        }
    }

    std::string term;
    term += character.value();
    auto nextChar = _fileReader.peek();
    while (nextChar) {
        if (nextChar.value() == WHITE_SPACE || nextChar.value() == NEW_LINE || _reservedKeywords.match(nextChar)) {
            return new Token(
                    _reservedKeywords.match(term)
                            .value_or(SymbolFactory::createIdentifierSymbol())
            );
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

void LexicalAnalyzer::stopIfNecessary() {
    if (!_fileReader.peek()) {
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
    for (int i = 0; i < numRetreats; ++i) {
        _fileReader.retreat();
    }
}


//
// Created by Johny Georges on 2023-12-31.
//

#include "lexical-analyzer.h"
#include "../../../shared/types/basic-character-type.h"
#include "../../symbol/symbol-factory.h"
#include "../../../shared/utils/logger/logger.h"

LexicalAnalyzer::LexicalAnalyzer() {
    _fileReader = FileReader();
    _reservedKeywords = ReservedKeywords();
    _hasMore = false;
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

std::optional<Token*> LexicalAnalyzer::buildNextToken() {
    auto character = _fileReader.advance();
    if (!character) {
        return {};
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
        if (nextChar && (
                nextChar.value() == WHITE_SPACE ||
                nextChar.value() == NEW_LINE ||
                _reservedKeywords.match(nextChar)
        )
                ) {
            return new Token(SymbolFactory::createIdentifierSymbol());
        }
        auto c = _fileReader.advance().value();
        term += c;
        auto isTermReservedKeyword = _reservedKeywords.match(term);
        if (isTermReservedKeyword) {
            return new Token(isTermReservedKeyword.value());
        }
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

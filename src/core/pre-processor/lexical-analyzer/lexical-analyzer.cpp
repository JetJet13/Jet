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
    _fileReader.open(filePath);
    if (_fileReader.peek()) {
        _hasMore = true;
    }
}

void LexicalAnalyzer::stop() {
    if (_fileReader.isOpen()) {
        _hasMore = false;
        _fileReader.close();
    }
}


std::optional<Lexeme> LexicalAnalyzer::next() {
    if (!_fileReader.isOpen()) {
        return {};
    }

    this->skipWhitespace();
    if (!_hasMore) {
        return {};
    }

    auto line = _fileReader.getPeekLine();
    auto position = _fileReader.getPeekPosition();
    auto nextToken = this->buildNextToken();
    this->stopIfNecessary();
    return Lexeme(nextToken, line, position);
}

bool LexicalAnalyzer::hasMore() const {
    return _hasMore;
}

Token* LexicalAnalyzer::buildNextToken() {
    Logger::log("buildNextToken ----------");
    std::string term;
    auto character = _fileReader.advance();
    auto line = _fileReader.getCurrentLine();
    auto position = _fileReader.getCurrentPosition();
    while (character) {
        auto c = character.value();
//        Logger::log("c:", c);

        auto isCharReservedKeyword = _reservedKeywords.match(c);
        if (isCharReservedKeyword) {
            if (term.empty()) {
                term += c;
            }

            auto tokenSymbol = _reservedKeywords.match(term)
                    .value_or(SymbolFactory::createIdentifierSymbol());

            return new Token(tokenSymbol);
        }

        if (c == WHITE_SPACE || c == NEW_LINE) {
            auto tokenSymbol = _reservedKeywords.match(term)
                    .value_or(SymbolFactory::createIdentifierSymbol());
            return new Token(tokenSymbol);
        }
        term += c;
        character = _fileReader.advance();
    }
    Logger::log("failed to build token for term:", term);
    throw std::runtime_error("failed to build token. Exiting...");
}

void LexicalAnalyzer::skipWhitespace() {
    auto c = _fileReader.peek();
    if (!c) {
        return;
    }
    while (c == WHITE_SPACE || c == NEW_LINE) {
        _fileReader.advance();
        c = _fileReader.peek();
    }
    this->stopIfNecessary();
}

void LexicalAnalyzer::stopIfNecessary() {
    if (!_fileReader.peek()) {
        stop();
    }
}

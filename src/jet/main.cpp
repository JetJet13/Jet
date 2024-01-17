//
// Created by Johny Georges on 2023-12-19.
//

#include <vector>
#include "main.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"
#include "../core/pre-processor/lexical-analyzer/lexical-analyzer.h"


int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        std::string filePath = argv[1];
        Logger::log("executing file:", filePath);
        auto tokenTable = new TokenTable();
        auto lexicalAnalyzer = LexicalAnalyzer(tokenTable);
        lexicalAnalyzer.start(filePath);
        auto lexeme = lexicalAnalyzer.next();
        while (lexeme) {

            Logger::log(lexeme->toString());
            if (lexeme->getToken()->getSymbol()->isInt()) {
                Logger::log("lexeme value", tokenTable->getInt(lexeme->getToken()->getValueId().value()).value());
            }

            if (lexeme.value().getToken()->getSymbol()->isFloat()) {
                Logger::log("lexeme value", tokenTable->getFloat(lexeme->getToken()->getValueId().value()).value());
            }

            if (lexeme.value().getToken()->getSymbol()->isChar()) {
                Logger::log("lexeme value", tokenTable->getChar(lexeme->getToken()->getValueId().value()).value());
            }

            if (lexeme.value().getToken()->getSymbol()->isString()) {
                Logger::log("lexeme value", tokenTable->getString(lexeme->getToken()->getValueId().value()).value());
            }

            Logger::log("peeking next lexeme...");
            auto peekNextLexeme = lexicalAnalyzer.peek();
            if (peekNextLexeme) {
                Logger::log(peekNextLexeme->toString());
            }
            Logger::log("---------------");
            lexeme = lexicalAnalyzer.next();
        }

    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}
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
        auto lexicalAnalyzer = LexicalAnalyzer();
        lexicalAnalyzer.start(filePath);
        while (lexicalAnalyzer.hasMore()) {
            Logger::log(lexicalAnalyzer.next()->toString());
        }

    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}
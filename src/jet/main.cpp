//
// Created by Johny Georges on 2023-12-19.
//

#include <vector>
#include "main.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"
#include "../core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../core/pre-processor/semantic-analyzer/semantic-analyzer.h"


int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        std::string filePath = argv[1];
        Logger::log("executing file:", filePath);
        auto tokenTable = new TokenTable();
        auto reservedKeywords = new ReservedKeywords();
        auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
        auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
        auto fileNode = syntaxAnalyzer.analyze(filePath);
        auto semanticAnalyzer = SemanticAnalyzer(new DependencyGraph());
        semanticAnalyzer.analyze(fileNode, new TypeSignatureLookupTable());

    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}
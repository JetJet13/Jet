//
// Created by Johny Georges on 2024-05-13.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/shared/utils/logger/logger.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/dependency-graph/dependency-graph.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"

TEST_CASE( "should print the expected type signatures" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto dependencyGraph = new DependencyGraph();
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();
    auto semanticAnalyzer = SemanticAnalyzer(dependencyGraph, tokenTable, typeSignatureLookupTable);
    semanticAnalyzer.analyze(fileNodeResult);
    Logger::log("===== TEST LOGS =====");
    typeSignatureLookupTable->dump();
    REQUIRE(fileNodeResult->getBody()->size() == 114);
    for (int i = 0; i < 114; i++) {
        auto declaration = fileNodeResult->getBody()->getContents()[i];
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        Logger::log("ID -", declaration->getId());
        Logger::log("TYPE SIGNATURE -", typeSignatureLookupTable->find(declaration->getId())->toString());
//        declaration->print();
//        Logger::log("RESULT =", declaration->isSameAs(expectedNodes[i + 1]));
//        REQUIRE(declaration->isSameAs(expectedNodes[i + 1]));
        Logger::log("====================================");
    }
}
//
// Created by Johny Georges on 2024-06-13.
//

#include <catch2/catch_all.hpp>
#include "../../../src/core/token/token-table.h"
#include "../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../src/core/pre-processor/semantic-analyzer/dependency-graph/dependency-graph.h"
#include "../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../src/vm/ir-generator/ir-generator.h"


TEST_CASE( "should create expected vm code" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto irGenerator = IRGenerator(tokenTable);
    auto irLookupTable = IRLookupTable();
    for (auto node : *fileNodeResult->getBody()) {
        irGenerator.generateFor(node, &irLookupTable);
    }
}
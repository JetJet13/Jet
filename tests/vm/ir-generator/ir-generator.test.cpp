//
// Created by Johny Georges on 2024-06-13.
//

#include <ostream>
#include <memory>
#include <catch2/catch_all.hpp>
#include "../../../src/core/token/token-table.h"
#include "../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../src/vm/ir-generator/ir-generator.h"
#include "resources/file-equality-checker/file-equality-checker.h"

TEST_CASE( "should create expected vm code" ) {
    std::string filePath = "./ir-generator-test-file.jet";
    std::string expectedOutputFilePath = "./ir-generator-test-expected-output.ir";
    std::string outputFileName = "ir-generator-test-output.ir";
    std::string outputFilePath = "./" + outputFileName;
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto irGenerator = IRGenerator();
    auto irLookupTable = IRLookupTable();
    std::error_code streamError;
    llvm::raw_fd_ostream ostream = llvm::raw_fd_ostream(outputFilePath, streamError, llvm::sys::fs::FileAccess('r'));
    for (auto node : *fileNodeResult->getBody()) {
        auto value = irGenerator.generateFor(node, &irLookupTable);
        value->print(ostream, false);
        ostream.write('\n');
        if (streamError.value() > 0) {
            throw std::logic_error(streamError.message());
        }
    }
    ostream.close();
    auto fileEqualityChecker = FileEqualityChecker();
    REQUIRE(fileEqualityChecker.areFilesEqual(expectedOutputFilePath, outputFilePath));
    Logger::log("FILES ARE EQUAL");
}
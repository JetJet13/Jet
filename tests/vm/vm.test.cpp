//
// Created by Johny Georges on 2024-06-13.
//

#include <ostream>
#include <memory>
#include "catch2/catch_all.hpp"
#include "../../src/core/token/token-table.h"
#include "../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../src/vm/ir-generator/ir-generator.h"
#include "utils/file-equality-checker/file-equality-checker.h"
#include "../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "../../src/core/pre-processor/pre-processor.h"
#include "../../src/vm/vm.h"

TEST_CASE("should create expected vm code") {
    std::string filePath = "./golden-master-test-file.jet";
    std::string expectedOutputFilePath = "./vm-test-expected-output.ir";
    std::string outputFileName = "vm-test-output.ir";
    std::string outputFilePath = "./" + outputFileName;
    auto tokenTable = std::make_shared<TokenTable>();
    auto reservedKeywords = std::make_shared<ReservedKeywords>();
    auto lexicalAnalyzer = std::make_shared<LexicalAnalyzer>(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = std::make_shared<SyntaxAnalyzer>(tokenTable, lexicalAnalyzer);
    auto semanticAnalyzer = std::make_shared<SemanticAnalyzer>();
    auto preProcessor = std::make_shared<PreProcessor>(syntaxAnalyzer, semanticAnalyzer);
    preProcessor->switchToDebugMode();
    auto jetFile = preProcessor->process(filePath);
    jetFile->getScope()->dump();
    jetFile->getTypeCheckerResult()->printErrors();
    REQUIRE(jetFile->getTypeCheckerResult()->ok());
    auto irInjector = std::make_shared<IRInjector>();
    auto irGenerator = std::make_shared<IRGenerator>(irInjector);
    std::error_code streamError;
    auto ostream = std::make_unique<llvm::raw_fd_ostream>(outputFilePath, streamError, llvm::sys::fs::FileAccess('r'));
    auto vm = new VM(irGenerator, irInjector);
    vm->switchToDebugMode();

    auto irJetFile = vm->compileMain(jetFile);
    irJetFile->getIRModule()->getModule()->get()->print(*ostream, nullptr);
    ostream->close();
    auto fileEqualityChecker = FileEqualityChecker();
    REQUIRE(fileEqualityChecker.areFilesEqual(outputFilePath, expectedOutputFilePath));
    Logger::log("FILES ARE EQUAL");
}
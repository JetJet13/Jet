//
// Created by Johny Georges on 2024-06-13.
//

#include "llvm/Linker/Linker.h"
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
#include "../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "../../../src/vm/ir-injector/ir-injector.h"
#include "../../../src/vm/ir-generator/ir-internal-modules/ir-util-internal-module/ir-util-internal-module.h"
#include "../../../src/core/pre-processor/pre-processor.h"

TEST_CASE( "should create expected vm code" ) {
    std::string filePath = "./ir-generator-test-file.jet";
    std::string expectedOutputFilePath = "./ir-generator-test-expected-output.ir";
    std::string outputFileName = "ir-generator-test-output.ir";
    std::string outputFilePath = "./" + outputFileName;
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = new SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto semanticAnalyzer = new SemanticAnalyzer();
    auto preprocessor = new PreProcessor(syntaxAnalyzer, semanticAnalyzer);
    auto jetFileResult = preprocessor->process(filePath);
    jetFileResult->getScope()->dump();
    jetFileResult->getTypeCheckerResult()->printErrors();
    REQUIRE(jetFileResult->getTypeCheckerResult()->ok());
    auto irInjector = new IRInjector();
    auto irGenerator = IRGenerator(irInjector);
    auto irModule = irGenerator.generateModule(filePath);
    irGenerator.initModule(irModule);
    auto irMainFunction = irGenerator.generateEmptyFunction("main", irModule);
    auto irMainFunctionBlock = irGenerator.generateFunctionBlock(irMainFunction->getFunction());
    auto irLookupTable = IRLookupTable();
    llvm::Linker::linkModules(
        *irModule->getModule(),
        std::unique_ptr<llvm::Module>(irGenerator.generateUtilInternalModule()->getModule())
    );
    std::error_code streamError;
    auto ostream = std::make_unique<llvm::raw_fd_ostream>(outputFilePath, streamError, llvm::sys::fs::FileAccess('r'));
    for (auto node : *jetFileResult->getFile()->getBody()) {
        auto value = irGenerator.generateFor((ASTDeclarationNode*)node, &irLookupTable, irModule);
        irInjector->inject(irMainFunctionBlock, value, irModule);
        if (streamError.value() > 0) {
            throw std::logic_error(streamError.message());
        }
    }
    irModule->getModule()->print(*ostream, nullptr);
    ostream->close();
    auto fileEqualityChecker = FileEqualityChecker();
    REQUIRE(fileEqualityChecker.areFilesEqual(expectedOutputFilePath, outputFilePath));
    Logger::log("FILES ARE EQUAL");
}
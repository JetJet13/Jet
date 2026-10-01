//
// Created by Johny Georges on 2026-09-05.
//

#include "main.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"
#include "../core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "../vm/ir-generator/ir-generator.h"
#include "../core/pre-processor/pre-processor.h"
#include "../vm/vm.h"
#include "types/supported-targets.h"
#include "types/target-linker-helper.h"

int main (int argc, const char* argv[]) {
    if (argc == 2) {
        std::string filePath = argv[1];
        auto tokenTable = std::make_shared<TokenTable>();
        auto reservedKeywords = std::make_shared<ReservedKeywords>();
        auto lexicalAnalyzer = std::make_shared<LexicalAnalyzer>(tokenTable, reservedKeywords);
        auto syntaxAnalyzer = std::make_shared<SyntaxAnalyzer>(tokenTable, lexicalAnalyzer);
        auto semanticAnalyzer = std::make_shared<SemanticAnalyzer>();
        auto preProcessor = PreProcessor(syntaxAnalyzer, semanticAnalyzer);
        auto jetFile = preProcessor.process(filePath);
        if (!preProcessor.getTypeCheckerResult()->ok()) {
            preProcessor.getTypeCheckerResult()->printErrors();
            exit(EXIT_STATUS_GENERIC_ERROR);
        }

        auto irInjector = std::make_shared<IRInjector>();
        auto irGenerator = std::make_shared<IRGenerator>(irInjector);

        // using new here avoids llvm 'use after deletion' errors from
        // being thrown
        auto vm = new VM(irGenerator, irInjector);

        auto irJetFile = vm->compileMain(jetFile);

        // Initialize the target registry etc.
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();
        std::string targetLookupError;


        auto TargetTriple = SUPPORTED_TARGETS.X86_MAC_OS_TARGET_TRIPLE;
        auto Target = llvm::TargetRegistry::lookupTarget(
                TargetTriple,
                targetLookupError
        );
        auto CPU = "generic";
        auto Features = "";

        llvm::TargetOptions opt;
        auto RM = std::optional<llvm::Reloc::Model>();
        auto TheTargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
        irJetFile->getIRModule()->getModule()->get()->setDataLayout(TheTargetMachine->createDataLayout());


        auto Filepath = std::filesystem::path(filePath);
        auto objectFilename = Filepath.parent_path().string() + "/" + Filepath.stem().string() + ".o";
        auto outputFilename = Filepath.parent_path().string() + "/" + Filepath.stem().string();
        std::error_code EC;
        llvm::raw_fd_ostream dest(objectFilename, EC, llvm::sys::fs::OF_None);

        if (EC) {
            Logger::log("Could not open file: ", EC.message());
            return 1;
        }

        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;

        if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            Logger::log("TheTargetMachine can't emit a file of this type");
            return EXIT_STATUS_GENERIC_ERROR;
        }

        pass.run(*irJetFile->getIRModule()->getModule()->get());
        dest.flush();

        return lld::lldMain(
                TargetLinkerHelper::getArgs(TargetTriple, &objectFilename, &outputFilename),
                llvm::outs(),
                llvm::errs(),
                LLD_ALL_DRIVERS
        ).retCode;

    } else {
        Logger::log("no jet file path provided..exiting");
    }

    return EXIT_STATUS_OK;
}
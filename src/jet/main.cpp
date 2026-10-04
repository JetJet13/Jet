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
#include "types/target-helper.h"
#include "types/cli-helper.h"

int main (int argc, const char* argv[]) {
    CLI::App app{"JET Compiler"};

    std::string filePath;
    std::string outDirectory;
    std::string macosSysLibDirectoryOverride;
    std::string linuxDynamicLinkerPathOverride;
    std::string linuxMultiArchPathOverride;
    std::string linuxLibDirOverride;
    bool includeObjectFile = false;

    CliHelper(&app)
    .addFilePathOption(filePath)
    ->addOutDirOption(outDirectory)
    ->addMacosSysLibDirOption(macosSysLibDirectoryOverride)
    ->addLinuxDynamicLinkerPathOverrideOption(linuxDynamicLinkerPathOverride)
    ->addLinuxMultiArchPathOverrideOption(linuxMultiArchPathOverride)
    ->addLinuxLibDirOverrideOption(linuxLibDirOverride)
    ->addIncludeObjectFileFlag(includeObjectFile);

    CLI11_PARSE(app, argc, argv)

    auto linkerArgBuilder = LinkerArgBuilder(
        macosSysLibDirectoryOverride,
        linuxDynamicLinkerPathOverride,
        linuxMultiArchPathOverride,
        linuxLibDirOverride
    );

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


    auto TargetTriple = TargetHelper::getLLVMTarget();
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
    if (outDirectory.empty()) {
        outDirectory = Filepath.parent_path().string();
    }
    auto objectFilename = std::filesystem::path(outDirectory).append(Filepath.stem().string() + ".o").string();
    auto outputFilename = std::filesystem::path(outDirectory).append(Filepath.stem().string()).string();
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
    TargetHelper::generateLinkerArgs(TargetTriple, objectFilename, outputFilename, &linkerArgBuilder);
    auto linkResult = lld::lldMain(
            linkerArgBuilder.build(),
            llvm::outs(),
            llvm::errs(),
            TargetHelper::getLinkerDrivers()
    );

    if (!includeObjectFile) {
        std::filesystem::remove(objectFilename);
    }

    return linkResult.retCode;
}
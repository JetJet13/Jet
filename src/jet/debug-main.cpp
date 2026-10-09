// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2023-12-19.
//


#include "debug-main.h"
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
    CLI::App app{"JET Debug Compiler"};

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

    Logger::log("executing file:", filePath);
    auto tokenTable = std::make_shared<TokenTable>();
    auto reservedKeywords = std::make_shared<ReservedKeywords>();
    auto lexicalAnalyzer = std::make_shared<LexicalAnalyzer>(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = std::make_shared<SyntaxAnalyzer>(tokenTable, lexicalAnalyzer);
    auto semanticAnalyzer = std::make_shared<SemanticAnalyzer>();
    auto preProcessor = PreProcessor(syntaxAnalyzer, semanticAnalyzer);
    preProcessor.switchToDebugMode();
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
    vm->switchToDebugMode();

    auto irJetFile = vm->compileMain(jetFile);

    Logger::log("IR Generation & Injection is done.");
    irJetFile->getIRModule()->getModule()->get()->print(llvm::outs(), nullptr);
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
        return 1;
    }

    pass.run(*irJetFile->getIRModule()->getModule()->get());
    dest.flush();
    Logger::log("Target Triple", TargetTriple);
    Logger::log("Data Layout", irJetFile->getIRModule()->getModule()->get()->getDataLayoutStr());
    Logger::log("Wrote ", objectFilename, "\n");
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
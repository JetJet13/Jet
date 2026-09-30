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

int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        std::string filePath = argv[1];
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

        auto const X86_MAC_OS_TARGET_TRIPLE = "x86_64-apple-darwin";
        auto const X86_LINUX_GNU_TARGET_TRIPLE = "x86_64-unknown-linux-gnu";
        auto const X86_LINUX_MUSL_TARGET_TRIPLE = "x86_64-unknown-linux-musl";
        auto const ARM64_MAC_OS_TARGET_TRIPLE = "aarch64-apple-darwin";
        auto const ARM64_LINUX_GNU_TARGET_TRIPLE = "aarch64-unknown-linux-gnu";
        auto const ARM64_LINUX_MUSL_TARGET_TRIPLE = "aarch64-unknown-linux-musl";
        auto TargetTriple = ARM64_LINUX_GNU_TARGET_TRIPLE;
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

        auto Filename = std::filesystem::path(filePath).stem().string();
        auto objectFilename = Filename + ".o";
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
        Logger::log("Wrote ", Filename, "\n");
        if (TargetTriple == X86_MAC_OS_TARGET_TRIPLE) {
            std::vector<const char*> args = {
                    "ld64.lld",
                    "-arch", "x86_64",
                    "-platform_version", "macos", "12.7", "13.0",
                    "-lc++",
                    "-lSystem",
                    "-syslibroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
                    objectFilename.c_str(),
                    "-o", Filename.c_str()
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        } else if (TargetTriple == ARM64_MAC_OS_TARGET_TRIPLE) {
            std::vector<const char*> args = {
                    "ld64.lld",
                    "-v",
                    "-arch", "arm64",
                    "-platform_version", "macos", "26.0", "26.0",
                    "-L /usr/local/llvm-17/lib",
                    "-lc++",
                    "-lSystem",
                    "-syslibroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
                    objectFilename.c_str(),
                    "-o", Filename.c_str()
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        } else if (TargetTriple == X86_LINUX_GNU_TARGET_TRIPLE) {
            std::vector<const char*> args = {
                    "ld.lld",
                    "-t",
                    "-z", "relro",
                    "-m", "elf_x86_64",
                    "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2",
                    "/usr/lib/x86_64-linux-gnu/crt1.o",
                    "/usr/lib/x86_64-linux-gnu/crti.o",
                    "-L/usr/lib/x86_64-linux-gnu",
                    "-L/usr/lib",
                    "-lc++",
                    "-lc++abi",
                    "-lunwind",
                    "-lm",
                    "-lc",
                    objectFilename.c_str(),
                    "-o", Filename.c_str(),
                    "/usr/lib/x86_64-linux-gnu/crtn.o",
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        } else if (TargetTriple == X86_LINUX_MUSL_TARGET_TRIPLE) {
            std::vector<const char*> args = {
                    "ld.lld",
                    "-t",
                    "-z", "relro",
                    "-m", "elf_x86_64",
                    "-dynamic-linker", "/lib/ld-musl-x86_64.so.1",
                    "/usr/lib/crt1.o",
                    "/usr/lib/crti.o",
                    "-L/usr/lib",
                    "-lc++",
                    "-lc++abi",
                    "-lm",
                    "-lc",
                    objectFilename.c_str(),
                    "-o", Filename.c_str(),
                    "/usr/lib/crtn.o",
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        } else if (TargetTriple == ARM64_LINUX_GNU_TARGET_TRIPLE) {
            Logger::log("using ARM64_LINUX_GNU_TARGET_TRIPLE LLD ARGS");
            std::vector<const char*> args = {
                    "ld.lld",
                    "-t",
                    "-z", "relro",
                    "-m", "aarch64elf",
                    "-dynamic-linker", "/lib/ld-linux-aarch64.so.1",
                    "/usr/lib/aarch64-linux-gnu/crt1.o",
                    "/usr/lib/aarch64-linux-gnu/crti.o",
                    "-L/usr/lib/aarch64-linux-gnu",
                    "-L/usr/lib",
                    "-lc++",
                    "-lc++abi",
                    "-lunwind",
                    "-lm",
                    "-lc",
                    objectFilename.c_str(),
                    "-o", Filename.c_str(),
                    "/usr/lib/aarch64-linux-gnu/crtn.o",
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        } else if (TargetTriple == ARM64_LINUX_MUSL_TARGET_TRIPLE) {
            std::vector<const char*> args = {
                    "ld.lld",
                    "-t",
                    "-z", "relro",
                    "-m", "aarch64linux",
                    "-dynamic-linker", "/lib/ld-musl-aarch64.so.1",
                    "/usr/lib/crt1.o",
                    "/usr/lib/crti.o",
                    "-L/usr/lib",
                    "-lc++",
                    "-lc++abi",
                    "-lm",
                    "-lc",
                    objectFilename.c_str(),
                    "-o", Filename.c_str(),
                    "/usr/lib/crtn.o",
            };
            return lld::lldMain(args, llvm::outs(), llvm::errs(), LLD_ALL_DRIVERS).retCode;
        }

    } else {
        Logger::log("no jet file path provided..exiting");
    }

    return EXIT_STATUS_OK;
}
//
// Created by Johny Georges on 2023-12-19.
//


#include "llvm/Linker/Linker.h"
#include "main.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"
#include "../core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "../vm/ir-generator/ir-generator.h"


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
        auto typeCheckerResult = semanticAnalyzer.analyze(fileNode, new TypeSignatureLookupTable());
        if (!typeCheckerResult.ok()) {
            Logger::log("type check failed");
            typeCheckerResult.print();
            return EXIT_STATUS_GENERIC_ERROR;
        }
        auto irInjector = new IRInjector();
        auto irGenerator = IRGenerator(irInjector);
        auto irModule = irGenerator.generateModule(filePath);
        irGenerator.initModule(irModule);
        llvm::Linker::linkModules(
                *irModule->getModule(),
                std::unique_ptr<llvm::Module>(irGenerator.generateUtilInternalModule()->getModule())
        );
        Logger::log("Done linking util internal module");
        auto irMainFunction = irGenerator.generateEmptyFunction("main", irModule);
        auto irMainFunctionBlock = irGenerator.generateFunctionBlock(irMainFunction->getFunction());
        auto irLookupTable = IRLookupTable();
        for (auto node : *fileNode->getBody()) {
            irInjector->inject(
                irMainFunctionBlock,
                irGenerator.generateFor((ASTDeclarationNode*)node, &irLookupTable, irModule),
                irModule
            );
        }
        irMainFunctionBlock->addVoidReturn();
        Logger::log("IR Generation & Injection is done.");
        irModule->getModule()->print(llvm::outs(), nullptr);
        // Initialize the target registry etc.
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();
        auto TargetTriple = llvm::sys::getDefaultTargetTriple();
        std::string Error;
        auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

        // Print an error and exit if we couldn't find the requested target.
        // This generally occurs if we've forgotten to initialise the
        // TargetRegistry or we have a bogus target triple.
        if (!Target) {
            Logger::log(Error);
            return 1;
        }

        auto CPU = "generic";
        auto Features = "";

        llvm::TargetOptions opt;
        auto RM = std::optional<llvm::Reloc::Model>();
        auto TheTargetMachine =
                Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

        irModule->getModule()->setDataLayout(TheTargetMachine->createDataLayout());

        auto Filename = "main-jet-test-file-output.o";
        std::error_code EC;
        llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

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

        pass.run(*irModule->getModule());
        dest.flush();

        Logger::log("Wrote ", Filename, "\n");

    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}
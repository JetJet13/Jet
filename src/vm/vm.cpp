//
// Created by Johny Georges on 2024-11-04.
//

#include "vm.h"
#include "../shared/utils/logger/logger.h"

VM::VM(IRGenerator* irGenerator, IRInjector* irInjector) {
    _irGenerator = irGenerator;
    _irInjector = irInjector;
}

IRJetFile* VM::compile(JetFile* jetFile) {
    auto irLookupTable = IRLookupTable();
    auto irModule = _irGenerator->generateModule(jetFile->getId());
    _irGenerator->initModule(irModule);
    auto irJetFile = new IRJetFile(jetFile, irModule);
    for (auto moduleToLink : *jetFile->getImportedFiles()) {
        this->linkJetFiles(this->compile(moduleToLink), irJetFile);
    }
    auto irMainFunction = _irGenerator->generateEmptyFunction(jetFile->getFile()->getPath()->filename().string(), irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    for (auto node : *jetFile->getFile()->getBody()) {
        _irInjector->inject(
                irMainFunctionBlock,
                _irGenerator->generateFor(node, &irLookupTable, irModule),
                irModule,
                &irLookupTable
        );
    }
    irMainFunctionBlock->addVoidReturn();
    return irJetFile;
}

IRJetFile* VM::compileMain(JetFile* jetFile) {
    auto irLookupTable = IRLookupTable();
    auto irModule = _irGenerator->generateModule(jetFile->getId());
    _irGenerator->initModule(irModule);
    auto irJetFile = new IRJetFile(jetFile, irModule);
    for (auto moduleToLink : *jetFile->getImportedFiles()) {
        this->linkJetFiles(this->compile(moduleToLink), irJetFile);
    }
    auto irMainFunction = _irGenerator->generateEmptyFunction("main", irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    for (auto node : *jetFile->getFile()->getBody()) {
        _irInjector->inject(
                irMainFunctionBlock,
                _irGenerator->generateFor(node, &irLookupTable, irModule),
                irModule,
                &irLookupTable
        );
    }
    irMainFunctionBlock->addVoidReturn();
    return irJetFile;
}

void VM::linkJetFiles(IRJetFile* source, IRJetFile* destination) {
    llvm::Linker::linkModules(
            *destination->getModule()->getModule(),
            std::unique_ptr<llvm::Module>(source->getModule()->getModule())
    );
    for (auto exportedDeclaration : *source->getFile()->getFile()->getModule().value()->getExports()) {
        auto exportedFunction = destination->getModule()->getModule()->getFunction(exportedDeclaration->getId());
        exportedFunction->setName(source->getFile()->getFile()->getModule().value()->getId() + "." + exportedDeclaration->getId());
    }
}
//
// Created by Johny Georges on 2024-11-04.
//

#include "vm.h"
#include "../shared/utils/logger/logger.h"
#include "ir-nodes/ir-context.h"

VM::VM(IRGenerator* irGenerator, IRInjector* irInjector) {
    _irGenerator = irGenerator;
    _irInjector = irInjector;
}

IRJetFile* VM::compile(JetFile* jetFile) {
    auto irLookupTable = IRLookupTable();
    auto irModule = _irGenerator->generateModule(jetFile->getId());
    _irGenerator->initModule(irModule);
    auto irJetFile = new IRJetFile(jetFile, irModule);
    this->linkJetUtilModule(irJetFile);
    for (auto moduleToLink : *jetFile->getImportedFiles()) {
        this->linkJetFiles(this->compile(moduleToLink), irJetFile);
    }
    auto irMainFunction = _irGenerator->generateMainFunction(jetFile->getFile()->getPath()->filename().string(),
                                                             irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto irContext = _irGenerator->generateContext(irMainFunctionBlock, irModule);
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generateInitialTypeFor(node, &irLookupTable, irContext);
    }
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generatePostInitialTypeFor(node, &irLookupTable, irContext);
    }
    auto generatedIRNodes = std::vector<IRNode*>();
    for (auto node : *jetFile->getFile()->getBody()) {
        generatedIRNodes.push_back(_irGenerator->generateFor(node, &irLookupTable, irContext));
    }
    for (auto irNode : generatedIRNodes) {
        _irInjector->inject(irMainFunctionBlock, irNode, irModule, &irLookupTable);
    }
    irMainFunctionBlock->getBuilder()->get()->CreateRet(irMainFunctionBlock->getBuilder()->get()->getInt32(0));
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
    auto irMainFunction = _irGenerator->generateMainFunction("main", irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto irContext = _irGenerator->generateContext(irMainFunctionBlock, irModule);
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generateInitialTypeFor(node, &irLookupTable, irContext);
    }
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generatePostInitialTypeFor(node, &irLookupTable, irContext);
    }
    auto generatedIRNodes = std::vector<IRNode*>();
    for (auto node : *jetFile->getFile()->getBody()) {
        generatedIRNodes.push_back(_irGenerator->generateFor(node, &irLookupTable, irContext));
    }
    for (auto irNode : generatedIRNodes) {
        _irInjector->inject(irMainFunctionBlock, irNode, irModule, &irLookupTable);
    }
    irMainFunctionBlock->getBuilder()->get()->CreateRet(irMainFunctionBlock->getBuilder()->get()->getInt32(0));
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

void VM::linkJetUtilModule(IRJetFile* source) {
    llvm::Linker::linkModules(
        *source->getModule()->getModule(),
        std::unique_ptr<llvm::Module>(_irGenerator->generateUtilInternalModule()->getModule())
    );
}
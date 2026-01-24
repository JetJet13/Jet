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

IRJetFile* VM::compile(JetFile* jetFile, std::shared_ptr<IRModuleNode> irCoreModule) {
    auto irLookupTable = IRLookupTable();
    auto irModule = _irGenerator->generateModule(jetFile->getId());
    irModule->linkTo(irCoreModule);
    auto irJetFile = new IRJetFile(jetFile, irModule);
    for (auto moduleToLink : *jetFile->getImportedFiles()) {
        this->linkJetFiles(this->compile(moduleToLink, irModule), irJetFile);
    }
    auto irMainFunction = _irGenerator->generateMainFunction(jetFile->getFile()->getPath()->filename().string(), irModule);
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
    auto irCoreModule = _irGenerator->generateCoreModule();
    _irGenerator->augmentUtilInternalModule(irCoreModule);
    _irGenerator->augmentDebugInternalModule(irCoreModule);
    auto irMainModule = _irGenerator->generateModule(jetFile->getId());
    irMainModule->linkTo(irCoreModule);
    auto irJetFile = new IRJetFile(jetFile, irMainModule);
    for (auto moduleToLink : *jetFile->getImportedFiles()) {
        this->linkJetFiles(this->compile(moduleToLink, irMainModule), irJetFile);
    }
    auto irMainFunction = _irGenerator->generateMainFunction("main", irMainModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto irContext = _irGenerator->generateContext(irMainFunctionBlock, irMainModule);
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generateInitialTypeFor(node, &irLookupTable, irContext);
    }
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generatePostInitialTypeFor(node, &irLookupTable, irContext);
    }

    auto generatedIRNodes = std::vector<IRNode*>();
    for (auto node : *jetFile->getFile()->getBody()) {
        irMainFunctionBlock->insert(_irGenerator->generateFor(node, &irLookupTable, irContext));
    }
    _irInjector->inject(irMainFunctionBlock, irMainFunctionBlock, irMainModule, &irLookupTable);
    irMainFunctionBlock->getLastSuccessorOrSelf()->getBuilder()->get()->CreateRet(irMainFunctionBlock->getBuilder()->get()->getInt32(0));
    return irJetFile;
}

void VM::linkJetFiles(IRJetFile* jetFileToLink, IRJetFile* destination) {
    for (auto exportedDeclaration : *jetFileToLink->getFile()->getFile()->getModule().value()->getExports()) {
        auto exportedFunction = destination->getIRModule()->getModule()->get()->getFunction(exportedDeclaration->getId());
        exportedFunction->setName(jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + exportedDeclaration->getId());
    }
}

//
// Created by Johny Georges on 2024-11-04.
//

#include "vm.h"
#include "../shared/utils/logger/logger.h"
#include "ir-nodes/ir-context.h"
#include "../shared/utils/function-id-generator/function-id-generator.h"
#include "utils/dependency-graph/dependency-graph.h"
#include "ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

VM::VM(IRGenerator* irGenerator, IRInjector* irInjector) {
    _irGenerator = irGenerator;
    _irInjector = irInjector;
    _jetFileMap = std::unordered_map<std::string, IRJetFile*>();
}

std::optional<IRJetFile*> VM::findCompiledJetFile(std::string id) {
    auto result = _jetFileMap.find(id);
    if (result == _jetFileMap.end()) {
        return {};
    }
    return result->second;
}

void VM::addCompiledJetFile(IRJetFile* irJetFile) {
    _jetFileMap.insert(std::pair(irJetFile->getFile()->getId(), irJetFile));
}

IRFunctionNode* VM::compile(IRJetFile* irJetFile, std::shared_ptr<IRModuleNode> irModule) {
    auto scope = irJetFile->getScope();
    auto jetFile = irJetFile->getFile();
    auto irMainFunction = _irGenerator->generateMainFunction(jetFile->getFile()->getPath()->filename().string(), irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto irContext = _irGenerator->generateContext(irMainFunctionBlock, irModule);
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generateInitialTypeFor(node, scope, irContext);
    }
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generatePostInitialTypeFor(node, scope, irContext);
    }
    auto generatedIRNodes = std::vector<IRNode*>();
    for (auto node : *jetFile->getFile()->getBody()) {
        generatedIRNodes.push_back(_irGenerator->generateFor(node, scope, irContext));
    }
    for (auto irNode : generatedIRNodes) {
        _irInjector->inject(irMainFunctionBlock, irNode, irModule, scope);
    }
    irMainFunctionBlock->getBuilder()->get()->CreateRet(irMainFunctionBlock->getBuilder()->get()->getInt32(0));
    return irMainFunction;
}

IRJetFile* VM::compileMain(JetFile* jetFile) {
    auto dependencyGraph = DependencyGraph();
    dependencyGraph.insert(jetFile);
    dependencyGraph.prioritize();
    dependencyGraph.dump();
    auto irCoreModule = _irGenerator->generateCoreModule();
    _irGenerator->augmentUtilInternalModule(irCoreModule);
    _irGenerator->augmentDebugInternalModule(irCoreModule);

    auto irMainModule = _irGenerator->generateModule(jetFile->getId());
    irMainModule->linkTo(irCoreModule);
    auto irMainFunction = _irGenerator->generateMainFunction("main", irMainModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());

    for (auto jetFileToCompile : *dependencyGraph.getPrioritizedList()) {
        Logger::log("Compiling", jetFileToCompile->getId());
        auto jetFileScope = new IRLookupTable();
        auto jetFileIRModule = _irGenerator->generateModule(jetFileToCompile->getId());
        auto irJetFileToCompile = new IRJetFile(jetFileToCompile, jetFileIRModule, jetFileScope);
        jetFileIRModule->linkTo(irCoreModule);
        for (auto importedFile : *jetFileToCompile->getImportedFiles()) {
            auto compiledJetFile = this->findCompiledJetFile(importedFile->getId()).value();
            this->linkJetFiles(compiledJetFile, irJetFileToCompile);
        }
        auto jetFileMainFunction = this->compile(irJetFileToCompile, jetFileIRModule);
        this->addCompiledJetFile(irJetFileToCompile);
        auto mainIRValue = irMainFunctionBlock->getBuilder()->get()->CreateCall(
                jetFileMainFunction->getFunction()
        );
        if (jetFileToCompile->getId() == jetFile->getId()) {
            auto mallocCounterVariable = irMainModule.get()->getModule()->get()->getGlobalVariable("DEBUG_MALLOC_COUNTER");
            auto mallocCounter = irMainFunctionBlock->getBuilder()->get()->CreateLoad(_irGenerator->generateIntType(), mallocCounterVariable);
            DebugIRInjectorHelper::injectLog(irMainFunctionBlock, "MALLOC COUNT", _irInjector, irMainModule);
            DebugIRInjectorHelper::injectLog(irMainFunctionBlock, mallocCounter, _irInjector, irMainModule);
            auto freeCounterVariable = irMainModule.get()->getModule()->get()->getGlobalVariable("DEBUG_FREE_COUNTER");
            auto freeCounter = irMainFunctionBlock->getBuilder()->get()->CreateLoad(_irGenerator->generateIntType(), freeCounterVariable);
            DebugIRInjectorHelper::injectLog(irMainFunctionBlock, "FREE COUNT", _irInjector, irMainModule);
            DebugIRInjectorHelper::injectLog(irMainFunctionBlock, freeCounter, _irInjector, irMainModule);
            irMainFunctionBlock->getBuilder()->get()->CreateRet(mainIRValue);
        }
    }
    return this->findCompiledJetFile(jetFile->getId()).value();
}

void VM::linkJetFiles(IRJetFile* jetFileToLink, IRJetFile* destination) {
    Logger::log("Linking JetFiles", jetFileToLink->getFile()->getId(), "to", destination->getFile()->getId());
    for (auto exportedDeclaration : *jetFileToLink->getFile()->getFile()->getModule().value()->getExports()) {
        if (exportedDeclaration->getTypeSignature()->isOneOf({ FUNCTION_TYPE_SOURCE, PROCEDURE_TYPE_SOURCE })) {
            auto invocableTypeSignature = (InvocableTypeSignature*)exportedDeclaration->getTypeSignature();
            auto irFunctionId = FunctionIdGenerator::generateFor(exportedDeclaration->getId(), invocableTypeSignature);
            auto declarationId = jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + irFunctionId;
            auto exportedFunction = destination->getIRModule()->getModule()->get()->getFunction(irFunctionId);
            if (exportedFunction != nullptr) {
                exportedFunction->setName(declarationId);
            }
            destination->getScope()->insertGlobalVariable(declarationId, jetFileToLink->getScope()->findGlobalVariable(irFunctionId).value());
        } else if (exportedDeclaration->isOneOf({ AST_VARIABLE_DECLARATION_NODE, AST_ENUM_DECLARATION_NODE }))  {
            auto declarationId = jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + exportedDeclaration->getId();
            auto globalExport = destination->getIRModule()->getModule()->get()->getGlobalVariable(exportedDeclaration->getId());
            if (globalExport != nullptr) {
                globalExport->setName(declarationId);
            }
            destination->getScope()->insertGlobalVariable(declarationId, jetFileToLink->getScope()->findGlobalVariable(exportedDeclaration->getId()).value());
        } else if (exportedDeclaration->is(AST_CLASS_DECLARATION_NODE)) {
            auto declarationId = jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + exportedDeclaration->getId();
            auto irClassType = jetFileToLink->getScope()->findGlobalType(exportedDeclaration->getId()).value();
            auto irClassValue = jetFileToLink->getScope()->findGlobalVariable(exportedDeclaration->getId()).value();
            destination->getScope()->insertGlobalType(declarationId, irClassType);
            destination->getScope()->insertGlobalVariable(declarationId, irClassValue);
            auto classDeclaration = (ASTClassDeclarationNode*)exportedDeclaration;
            for (auto staticProperty : *classDeclaration->getBlock()->getStaticProperties()) {
                if (staticProperty->isPublic()) {
                    destination->getScope()->insertGlobalVariable(declarationId, jetFileToLink->getScope()->findGlobalVariable(staticProperty->getId()).value());
                }
            }
        }
    }
}
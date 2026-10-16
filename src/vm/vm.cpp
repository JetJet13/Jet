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
// Created by Johny Georges on 2024-11-04.
//

#include "vm.h"
#include "../shared/utils/logger/logger.h"
#include "../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"
#include "utils/dependency-graph/dependency-graph.h"
#include "ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "ir-injector/ir-injector-strategies/ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"

VM::VM(std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRInjector> irInjector) {
    _debugMode = false;
    _irGenerator = irGenerator;
    _irInjector = irInjector;
    _jetFileMap = std::unordered_map<std::string, std::shared_ptr<IRJetFile>>();
}

void VM::switchToDebugMode() {
    _debugMode = true;
    _irGenerator->switchToDebugMode();
    _irInjector->switchToDebugMode();
    DebugIRInjectorHelper::enable();
}

std::optional<std::shared_ptr<IRJetFile>> VM::findCompiledJetFile(std::string id) {
    auto result = _jetFileMap.find(id);
    if (result == _jetFileMap.end()) {
        return {};
    }
    return result->second;
}

void VM::addCompiledJetFile(std::shared_ptr<IRJetFile> irJetFile) {
    _jetFileMap.insert(std::pair(irJetFile->getFile()->getId(), irJetFile));
}

std::shared_ptr<IRFunctionNode> VM::compile(std::shared_ptr<IRJetFile> irJetFile, std::shared_ptr<IRModuleNode> irModule) {
    auto scope = irJetFile->getScope();
    auto jetFile = irJetFile->getFile();
    auto irMainFunction = _irGenerator->generateMainFunction(jetFile->getFile()->getPath().filename().string(), irModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto irContext = _irGenerator->generateContext(irMainFunctionBlock, irModule);
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generateInitialTypeFor(node, scope, irContext);
    }
    for (auto node : *jetFile->getFile()->getBody()) {
        _irGenerator->generatePostInitialTypeFor(node, scope, irContext);
    }
    auto generatedIRNodes = std::vector<std::shared_ptr<IRNode>>();
    for (auto node : *jetFile->getFile()->getBody()) {
        generatedIRNodes.push_back(_irGenerator->generateFor(node, scope, irContext));
    }
    for (auto irNode : generatedIRNodes) {
        _irInjector->inject(irMainFunctionBlock->getLastChildOrSelf(), irNode, irModule, scope);
    }
    DebugIRInjectorHelper::injectFunctionEnterLog(irMainFunctionBlock, jetFile->getFile()->getModuleName(), _irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irMainFunctionBlock, jetFile->getFile()->getModuleName(), _irInjector, irModule);
    FreeIRInjectorHelper::freeFunctionBlockNodes(irMainFunctionBlock, _irInjector, irModule, scope);
    irMainFunctionBlock->getLastChildOrSelf()->getBuilder()->get()->CreateRet(irMainFunctionBlock->getBuilder()->get()->getInt32(0));
    return irMainFunction;
}

std::shared_ptr<IRJetFile> VM::compileMain(std::shared_ptr<JetFile> jetFile) {
    auto dependencyGraph = DependencyGraph();
    dependencyGraph.insert(jetFile);
    dependencyGraph.prioritize();
    auto irCoreModule = _irGenerator->generateCoreModule();
    _irGenerator->augmentUtilInternalModule(irCoreModule);
    if (_debugMode) {
        _irGenerator->augmentDebugInternalModule(irCoreModule);
        dependencyGraph.dump();
    }

    auto irMainModule = _irGenerator->generateModule(jetFile->getId());
    irMainModule->linkTo(irCoreModule);
    auto irMainFunction = _irGenerator->generateMainFunction("main", irMainModule);
    auto irMainFunctionBlock = _irGenerator->generateFunctionBlock(irMainFunction->getFunction());
    auto prioritizedList = dependencyGraph.getPrioritizedList();
    for (auto jetFileToCompile : *prioritizedList) {
        Logger::debugLog(_debugMode, "Compiling", jetFileToCompile->getId());
        auto jetFileScope = std::make_shared<IRLookupTable>(jetFileToCompile->getFile()->getModuleName());
        auto jetFileIRModule = _irGenerator->generateModule(jetFileToCompile->getId());
        auto irJetFileToCompile = std::make_shared<IRJetFile>(jetFileToCompile, jetFileIRModule, jetFileScope);
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
            if (_debugMode) {
                auto mallocCounterVariable = irMainModule.get()->getModule()->get()->getGlobalVariable("DEBUG_MALLOC_COUNTER");
                auto mallocCounter = irMainFunctionBlock->getBuilder()->get()->CreateLoad(_irGenerator->generateIntType(), mallocCounterVariable);
                DebugIRInjectorHelper::injectLog(irMainFunctionBlock, "MALLOC COUNT", _irInjector, irMainModule);
                DebugIRInjectorHelper::injectLog(irMainFunctionBlock, mallocCounter, _irInjector, irMainModule);
                auto freeCounterVariable = irMainModule.get()->getModule()->get()->getGlobalVariable("DEBUG_FREE_COUNTER");
                auto freeCounter = irMainFunctionBlock->getBuilder()->get()->CreateLoad(_irGenerator->generateIntType(), freeCounterVariable);
                DebugIRInjectorHelper::injectLog(irMainFunctionBlock, "FREE COUNT", _irInjector, irMainModule);
                DebugIRInjectorHelper::injectLog(irMainFunctionBlock, freeCounter, _irInjector, irMainModule);
                DebugIRInjectorHelper::injectFunctionEnterLog(irMainFunctionBlock, jetFile->getId(), _irInjector, irMainModule);
                DebugIRInjectorHelper::injectFunctionExitLog(irMainFunctionBlock, jetFile->getId(), _irInjector, irMainModule);
            }
            irMainFunctionBlock->getBuilder()->get()->CreateRet(mainIRValue);
        }
    }
    return this->findCompiledJetFile(jetFile->getId()).value();
}

void VM::linkJetFiles(std::shared_ptr<IRJetFile> jetFileToLink, std::shared_ptr<IRJetFile> destination) {
    Logger::debugLog(_debugMode, "Linking JetFiles", jetFileToLink->getFile()->getId(), "to", destination->getFile()->getId());
    destination->getScope()->link(jetFileToLink->getScope());
    for (auto exportedDeclaration : *jetFileToLink->getFile()->getFile()->getModule().value()->getExports()) {
        if (exportedDeclaration->getTypeSignature()->isOneOf({ FUNCTION_TYPE_SOURCE, PROCEDURE_TYPE_SOURCE })) {
            auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(exportedDeclaration->getTypeSignature());
            auto irFunctionId = FunctionIdGenerator::generateFor(exportedDeclaration->getId(), invocableTypeSignature);
            auto declarationId = jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + irFunctionId;
            auto exportedFunction = destination->getIRModule()->getModule()->get()->getFunction(irFunctionId);
            if (exportedFunction != nullptr) {
                exportedFunction->setName(declarationId);
            }
        } else if (exportedDeclaration->isOneOf({ AST_VARIABLE_DECLARATION_NODE, AST_ENUM_DECLARATION_NODE }))  {
            auto declarationId = jetFileToLink->getFile()->getFile()->getModule().value()->getId() + "." + exportedDeclaration->getId();
            auto globalExport = destination->getIRModule()->getModule()->get()->getGlobalVariable(exportedDeclaration->getId());
            if (globalExport != nullptr) {
                globalExport->setName(declarationId);
            }
        }
    }
}
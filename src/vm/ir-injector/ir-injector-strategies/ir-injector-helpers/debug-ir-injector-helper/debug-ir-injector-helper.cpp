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
// Created by Johny Georges on 2025-12-13.
//

#include "debug-ir-injector-helper.h"

void DebugIRInjectorHelper::enable() {
    DebugIRInjectorHelper::_debugMode = true;
}

void DebugIRInjectorHelper::disable() {
    DebugIRInjectorHelper::_debugMode = false;
}

void DebugIRInjectorHelper::injectFunctionEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->setInsertionPointBeforeFirstInstruction();
    irBlockNode->getBuilder()->get()->CreateCall(
        irModule->getPrintDebugStringFunction(),
        {
                irInjector->injectRawString(irBlockNode, "[enter] " +  functionName + "\n")
        }
    );
    irBlockNode->resetInsertionPoint();
}

void DebugIRInjectorHelper::injectFunctionExitLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->setInsertionPointBeforeLastInstruction();
    irBlockNode->getLastChildOrSelf()->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                irInjector->injectRawString(irBlockNode->getLastChildOrSelf(), "[exit] " + functionName + "\n")
            }
    );
    irBlockNode->resetInsertionPoint();
}

void DebugIRInjectorHelper::injectControlFlowEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->setInsertionPointBeforeFirstInstruction();
    irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                    irInjector->injectRawString(irBlockNode, "[enter] ControlFlow: " +  std::to_string(index) + "\n")
            }
    );
    irBlockNode->resetInsertionPoint();
}

void DebugIRInjectorHelper::injectControlFlowExitLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->setInsertionPointBeforeLastInstruction();
    irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                irInjector->injectRawString(irBlockNode, "[exit] ControlFlow: " +  std::to_string(index) + "\n")
            }
    );
    irBlockNode->resetInsertionPoint();
}

void DebugIRInjectorHelper::injectRefCountLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* idValue, llvm::Value* refValue, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    auto refCount = irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getGetRefCountFunction(),
            { refValue }
    );
    irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugRefCountFunction(),
            { idValue, refCount }
    );
}

void DebugIRInjectorHelper::injectLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    auto logAsDebugMarker = irBlockNode->getBuilder()->get()->CreateZExt(log, irBlockNode->getBuilder()->get()->getInt64Ty());
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintDebugMarkerFunction(), { logAsDebugMarker });
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintNewLineFunction());
}

void DebugIRInjectorHelper::injectLog(std::shared_ptr<IRBlockNode> irBlockNode, int log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->getBuilder()->get()->CreateCall(
        irModule->getPrintDebugMarkerFunction(),
        {
            irBlockNode->getBuilder()->get()->getInt64(log)
        }
    );
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintNewLineFunction());
}

void DebugIRInjectorHelper::injectLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string log, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                irInjector->injectRawString(irBlockNode, log + "\n")
            }
    );
}
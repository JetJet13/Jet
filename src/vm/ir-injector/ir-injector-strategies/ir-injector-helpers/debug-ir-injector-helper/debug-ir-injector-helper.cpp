//
// Created by Johny Georges on 2025-12-13.
//

#include "debug-ir-injector-helper.h"

void DebugIRInjectorHelper::injectFunctionEnterLog(IRBlockNode* irBlockNode, std::string functionName, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
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

void DebugIRInjectorHelper::injectFunctionExitLog(IRBlockNode* irBlockNode, std::string functionName, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->setInsertionPointBeforeLastInstruction();
    irBlockNode->getLastSuccessorOrSelf()->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                irInjector->injectRawString(irBlockNode->getLastSuccessorOrSelf(), "[exit] " +  functionName + "\n")
            }
    );
    irBlockNode->resetInsertionPoint();
}

void DebugIRInjectorHelper::injectControlFlowEnterLog(IRBlockNode* irBlockNode, int index, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
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

void DebugIRInjectorHelper::injectControlFlowExitLog(IRBlockNode* irBlockNode, int index, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
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

void DebugIRInjectorHelper::injectRefCountLog(IRBlockNode* irBlockNode, llvm::Value* idValue, llvm::Value* refValue, std::shared_ptr<IRModuleNode> irModule) {
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

void DebugIRInjectorHelper::injectLog(IRBlockNode* irBlockNode, llvm::Value* log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintDebugMarkerFunction(), { log });
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintNewLineFunction());
}

void DebugIRInjectorHelper::injectLog(IRBlockNode* irBlockNode, int log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->getBuilder()->get()->CreateCall(
        irModule->getPrintDebugMarkerFunction(),
        {
            irBlockNode->getBuilder()->get()->getInt64(log)
        }
    );
    irBlockNode->getBuilder()->get()->CreateCall(irModule->getPrintNewLineFunction());
}

void DebugIRInjectorHelper::injectLog(IRBlockNode* irBlockNode, std::string log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule) {
    if (!DebugIRInjectorHelper::_debugMode) return;
    irBlockNode->getBuilder()->get()->CreateCall(
            irModule->getPrintDebugStringFunction(),
            {
                irInjector->injectRawString(irBlockNode, log + "\n")
            }
    );
}
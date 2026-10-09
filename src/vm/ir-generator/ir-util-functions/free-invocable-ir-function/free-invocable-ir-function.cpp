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
// Created by Johny Georges on 2026-01-01.
//

#include "free-invocable-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeInvocableIRFunction::getFreeInvocableIRFunctionName() {
    return "jet.free.invocable";
}

void FreeInvocableIRFunction::declareFreeInvocableFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeInvocableIRFunction::getFreeInvocableIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeInvocableIRFunction::generateFreeInvocableFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto intType = irGenerator->generateIntType();
    auto boolType = irGenerator->generateBooleanType();
    auto irInvocableType = irGenerator->generateIRInvocableType();

    auto function = irModuleNode->getFreeInvocableFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto freeInvocableIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto freeInvocableIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto freeInvocableIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto freeInvocableEndBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionRefCounterIndex());
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(intType, refCounterPointer, "currentRefCount");
    auto pointerToIsPerpetual = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getIsPerpetualIndex());
    auto isPerpetual = functionBlock->getBuilder()->get()->CreateLoad(boolType, pointerToIsPerpetual, "isPerpetual");
    DebugIRInjectorHelper::injectLog(functionBlock, "IS PERPETUAL?", irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(functionBlock, isPerpetual, irGenerator->getInjector(), irModuleNode);
    functionBlock->getBuilder()->get()->CreateCondBr(isPerpetual, freeInvocableEndBlock->getBlock(), freeInvocableIfBlock->getBlock());
    auto isLastRef = freeInvocableIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeInvocableIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeInvocableIfThenBlock->getBlock(), freeInvocableIfElseBlock->getBlock());

    DebugIRInjectorHelper::injectLog(freeInvocableIfThenBlock, "FREEING INVOCABLE!", irGenerator->getInjector(), irModuleNode);
    freeInvocableIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeLambdaFunction(),
            { function->getArg(0) }
    );
    DebugIRInjectorHelper::injectLog(freeInvocableIfThenBlock, "DONE FREEING INVOCABLE!", irGenerator->getInjector(), irModuleNode);
    freeInvocableIfThenBlock->getBuilder()->get()->CreateBr(freeInvocableEndBlock->getBlock());

    auto newRefCount = freeInvocableIfElseBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeInvocableIfElseBlock->getBuilder()->get()->CreateStore(newRefCount, refCounterPointer);
    DebugIRInjectorHelper::injectLog(freeInvocableIfElseBlock, "DECREMENTED INVOCABLE REF COUNT!", irGenerator->getInjector(), irModuleNode);
    freeInvocableIfElseBlock->getBuilder()->get()->CreateBr(freeInvocableEndBlock->getBlock());

    freeInvocableEndBlock->addVoidReturn();
}
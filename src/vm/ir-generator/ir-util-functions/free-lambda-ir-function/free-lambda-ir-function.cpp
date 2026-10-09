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
// Created by Johny Georges on 2025-12-10.
//

#include "free-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeLambdaIRFunction::getFreeLambdaIRFunctionName() {
    return "jet.free.lambda";
}

void FreeLambdaIRFunction::declareFreeLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeLambdaIRFunction::getFreeLambdaIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeLambdaIRFunction::generateFreeLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType(std::make_shared<IRType>(intType));
    auto irInvocableType = irGenerator->generateIRInvocableType();

    auto function = irModuleNode->getFreeLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto freeLambdaIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto freeLambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto freeLambdaEndBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionRefCounterIndex());
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(intType, refCounterPointer, "currentRefCount");
    functionBlock->getBuilder()->get()->CreateBr(freeLambdaIfBlock->getBlock());

    auto isLastRef = freeLambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeLambdaIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeLambdaIfThenBlock->getBlock(), freeLambdaEndBlock->getBlock());

    auto pointerToLambdaScope = freeLambdaIfThenBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionScopeArgumentIndex());
    auto loadedLambdaScope = InstructionIRInjectorHelper::injectLoad(irInvocableType->getFunctionScopeArgumentType(), pointerToLambdaScope, freeLambdaIfThenBlock);
    auto pointerToCleanupFunction = freeLambdaIfThenBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionCleanupIndex());
    auto loadedCleanupFunction = InstructionIRInjectorHelper::injectLoad(irInvocableType->getFunctionCleanupType(), pointerToCleanupFunction, freeLambdaIfThenBlock);
    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irInvocableType->getCleanupFunctionType(),
            loadedCleanupFunction,
            {
                loadedLambdaScope
            }
    );
    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            {
                loadedLambdaScope
            }
    );
    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            {
                refCounterPointer
            }
    );
    DebugIRInjectorHelper::injectLog(freeLambdaIfThenBlock, "DONE FREEING LAMBDA!", irGenerator->getInjector(), irModuleNode);
    freeLambdaIfThenBlock->getBuilder()->get()->CreateBr(freeLambdaEndBlock->getBlock());

    freeLambdaEndBlock->addVoidReturn();
}
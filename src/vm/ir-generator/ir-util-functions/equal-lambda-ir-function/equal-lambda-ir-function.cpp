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
// Created by Johny Georges on 2026-01-21.
//

#include "equal-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualLambdaIRFunction::getEqualLambdaIRFunctionName() {
    return "jet.equal.lambda";
}

void EqualLambdaIRFunction::declareEqualLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualLambdaIRFunction::getEqualLambdaIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualLambdaIRFunction::generateEqualLambdaFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irInvocableType = irGenerator->generateIRInvocableType();
    auto function = irModuleNode->getEqualLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto firstLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionIndex());
    auto firstLambdaFunction = InstructionIRInjectorHelper::injectLoad(pointerType, firstLambdaFunctionPointer, functionBlock);
    auto secondLambdaFunctionPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(1), irInvocableType->getFunctionIndex());
    auto secondLambdaFunction = InstructionIRInjectorHelper::injectLoad(pointerType, secondLambdaFunctionPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            firstLambdaFunction,
            secondLambdaFunction
        )
    );

}
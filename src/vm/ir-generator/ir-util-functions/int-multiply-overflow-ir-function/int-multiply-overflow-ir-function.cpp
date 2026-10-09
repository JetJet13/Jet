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
// Created by Johny Georges on 2026-05-16.
//

#include "int-multiply-overflow-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string IntMultiplyOverflowIRFunction::getIntMultiplyOverflowIRFunctionName() {
    return "jet.int.multiply.overflow";
}

void IntMultiplyOverflowIRFunction::generateIntMultiplyOverflowFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto raise = irModuleNode->getModule()->get()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(intType, { intType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, IntMultiplyOverflowIRFunction::getIntMultiplyOverflowIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isOverflowBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(),  "is.overflow");
    auto elseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());

    auto result = functionBlock->getBuilder()->get()->CreateBinaryIntrinsic(
            llvm::Intrinsic::smul_with_overflow,
            function->getArg(0),
            function->getArg(1)
    );
    auto overflowResult = functionBlock->getBuilder()->get()->CreateExtractValue(result, 1);
    auto isOverflow = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            overflowResult,
            irGenerator->generateBoolean(true)
    );

    functionBlock->getBuilder()->get()->CreateCondBr(
            isOverflow,
            isOverflowBlock->getBlock(),
            elseBlock->getBlock()
    );
    auto overflowMessage = irGenerator->generateRawString("Error [JET1003]: Int Multiplication Operation caused overflow \n");
    auto overflowMessageAlloca = isOverflowBlock->getBuilder()->get()->CreateAlloca(overflowMessage->getType());
    isOverflowBlock->getBuilder()->get()->CreateStore(overflowMessage, overflowMessageAlloca);
    isOverflowBlock->getBuilder()->get()->CreateCall(printf, { overflowMessageAlloca });
    auto sigTermCode = irGenerator->generateIntConstant(15);
    isOverflowBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    isOverflowBlock->getBuilder()->get()->CreateRet(irGenerator->generateIntConstant(0));

    auto value = elseBlock->getBuilder()->get()->CreateExtractValue(result, 0);
    elseBlock->getBuilder()->get()->CreateRet(value);
}
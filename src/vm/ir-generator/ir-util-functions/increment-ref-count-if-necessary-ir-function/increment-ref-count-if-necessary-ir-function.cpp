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
// Created by Johny Georges on 2026-02-12.
//

#include "increment-ref-count-if-necessary-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"

std::string IncrementRefCountIfNecessaryIRFunction::getIncrementRefCountIfNecessaryIRFunctionName() {
    return "jet.increment.ref.count.if.necessary";
}

void IncrementRefCountIfNecessaryIRFunction::generateIncrementRefCountIfNecessaryFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, IncrementRefCountIfNecessaryIRFunction::getIncrementRefCountIfNecessaryIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto refIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "ref.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto lambdaIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "lambda.");
    auto lambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "lambda.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getIdIndex() });
    
    functionBlock->getBuilder()->get()->CreateBr(refIfBlock->getBlock());

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getIncrementRefCountFunction(),
        {
            function->getArg(0)
        }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), lambdaIfBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getIncrementRefCountFunction(),
        {
            function->getArg(0)
        }
    );

    auto isValueTypeLambda = lambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE)
    );
    lambdaIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeLambda, lambdaIfThenBlock->getBlock(), endBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getIncrementLambdaRefCountFunction(),
        {
            function->getArg(0)
        }
    );

    refIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->addVoidReturn();
}
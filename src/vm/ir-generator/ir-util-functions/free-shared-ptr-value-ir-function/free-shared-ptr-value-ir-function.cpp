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
// Created by Johny Georges on 2026-02-24.
//

#include "free-shared-ptr-value-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"

std::string FreeSharedPtrValueIRFunction::getFreeSharedPtrValueIRFunctionName() {
    return "jet.free.shared.ptr.value";
}

void FreeSharedPtrValueIRFunction::generateFreeSharedPtrValueFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeSharedPtrValueIRFunction::getFreeSharedPtrValueIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    DebugIRInjectorHelper::injectLog(functionBlock, "FREEING REF VALUE FUNCTION!", irGenerator->getInjector(), irModuleNode);
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getIdIndex() });
    functionBlock->getBuilder()->get()->CreateBr(structRefIfBlock->getBlock());

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), structRefElseBlock->getBlock());
    DebugIRInjectorHelper::injectLog(structRefIfThenBlock, "FREEING REF-VALUE STRUCT_REF!", irGenerator->getInjector(), irModuleNode);
    auto structTypePointer = structRefIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getAllocIndex() });
    auto loadedStructType = structRefIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto pointerToStructPointer = structRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    auto structPointer = structRefIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToStructPointer);
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction(),
            { structPointer, loadedStructType }
    );

    structRefElseBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getFreeValueFunction(),
        {
            function->getArg(0),
            function->getArg(1)
        }
    );

    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefElseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    endBlock->addVoidReturn();
}
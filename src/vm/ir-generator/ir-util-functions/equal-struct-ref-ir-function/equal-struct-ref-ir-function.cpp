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
// Created by Johny Georges on 2025-12-22.
//

#include "equal-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string EqualStructRefIRFunction::getEqualStructRefIRFunctionName() {
    return "jet.equal.struct.ref";
}

void EqualStructRefIRFunction::declareEqualStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualStructRefIRFunction::getEqualStructRefIRFunctionName(), irModuleNode->getModule()->get());
}


void EqualStructRefIRFunction::generateEqualStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto function = irModuleNode->getEqualStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto structTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto loadedStructType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto firstStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    auto loadedFirstStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, firstStructPointer, functionBlock);

    auto secondStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getStructIndex());
    auto loadedSecondStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, secondStructPointer, functionBlock);

    auto result = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualStructFunction(),
            { loadedFirstStructPointer, loadedSecondStructPointer, loadedStructType }
    );
    functionBlock->getBuilder()->get()->CreateRet(result);
}
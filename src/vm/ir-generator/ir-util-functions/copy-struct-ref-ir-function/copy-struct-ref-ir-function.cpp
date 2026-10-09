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
// Created by Johny Georges on 2025-12-19.
//

#include "copy-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyStructRefIRFunction::getCopyStructRefIRFunctionName() {
    return "jet.copy.struct.ref";
}

void CopyStructRefIRFunction::declareCopyStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStructRefIRFunction::getCopyStructRefIRFunctionName(), irModuleNode->getModule()->get());
}

void CopyStructRefIRFunction::generateCopyStructRefFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto structTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto loadedStructType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto structTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(loadedStructType, { typeValueType->getSizeInBytesIndex() });
    auto structMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(1), structTypeSizeInBytes }
    );
    auto counterMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateIntConstant(structRefType->getCounterIRType()->getSizeInBytes()),
            }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), counterMalloc, functionBlock);
    auto sourceStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getStructIndex());
    auto loadedSourceStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, sourceStructPointer, functionBlock);

    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyStructFunction(),
            { structMalloc, loadedSourceStructPointer, loadedStructType }
    );
    auto pointerToNewStructRefStruct = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    InstructionIRInjectorHelper::injectStore(structMalloc, pointerToNewStructRefStruct, functionBlock);
    auto pointerToNewStructRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getCounterIndex());
    InstructionIRInjectorHelper::injectStore(counterMalloc, pointerToNewStructRefCounter, functionBlock);
    functionBlock->addVoidReturn();
}
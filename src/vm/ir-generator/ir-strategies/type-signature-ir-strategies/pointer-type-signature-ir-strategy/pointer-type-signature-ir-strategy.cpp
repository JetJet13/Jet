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
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"

std::shared_ptr<IRPointerType> PointerTypeSignatureIRStrategy::generate(std::shared_ptr<PointerTypeSignature> pointerTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto underlyingIRType = irGenerator->generateTypeFor(pointerTypeSignature->getUnderlyingType(), scope, irContext);
    auto irPointerType = IRPointerType::create(underlyingIRType);
    irPointerType->setValue(this->generateTypeValue(irPointerType, irGenerator));
    return irPointerType;
}

std::shared_ptr<IRTypeValueInstructionNode> PointerTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRGenerator> irGenerator) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.POINTER),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return std::make_shared<IRTypeValueInstructionNode>(
        allocation,
        irGenerator->generateIrPointerType(irTypeValueType),
        storeInstruction
    );
}
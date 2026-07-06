//
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"

std::shared_ptr<IRPointerType> PointerTypeSignatureIRStrategy::generate(std::shared_ptr<PointerTypeSignature> pointerTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto underlyingIRType = irGenerator->generateTypeFor(pointerTypeSignature->getUnderlyingType(), scope, irContext);
    auto irPointerType = IRPointerType::create(underlyingIRType);
    irPointerType->setValue(this->generateTypeValue(irPointerType, irGenerator));
    return irPointerType;
}

std::shared_ptr<IRTypeValueInstructionNode> PointerTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRPointerType> irType, IRGenerator* irGenerator) {
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
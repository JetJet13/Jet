//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"

std::shared_ptr<IRRefType> RefTypeSignatureIRStrategy::generate(std::shared_ptr<RefTypeSignature> refTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto underlyingIRType = irGenerator->generateTypeFor(refTypeSignature->getUnderlyingType(), scope, irContext);
    auto irRefType = irGenerator->generateIrRefType(underlyingIRType);
    irRefType->setValue(this->generateTypeValue(irRefType, irGenerator, irContext));
    return irRefType;
}

std::shared_ptr<IRTypeValueInstructionNode> RefTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRRefType> irType, IRGenerator* irGenerator, std::shared_ptr<IRContext> irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.REF),
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
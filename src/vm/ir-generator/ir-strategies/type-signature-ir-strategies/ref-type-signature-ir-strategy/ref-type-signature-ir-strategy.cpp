//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"

IRRefType* RefTypeSignatureIRStrategy::generate(RefTypeSignature* refTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto underlyingIRType = irGenerator->generateTypeFor(refTypeSignature->getUnderlyingType(), scope, irContext);
    auto irRefType = irGenerator->generateIrRefType(underlyingIRType);
    irRefType->setValue(this->generateTypeValue(irRefType, irGenerator));
    return irRefType;
}

IRInstructionNode* RefTypeSignatureIRStrategy::generateTypeValue(IRRefType* irType, IRGenerator* irGenerator) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.REF),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return new IRInstructionNode(
            allocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            {},
            { storeInstruction }
    );
}
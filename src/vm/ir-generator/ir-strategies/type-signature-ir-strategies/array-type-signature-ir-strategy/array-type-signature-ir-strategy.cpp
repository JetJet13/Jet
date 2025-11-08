//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/logger/logger.h"

IRArrayPointerType* ArrayTypeSignatureIRStrategy::generate(ArrayTypeSignature* arrayTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType(), scope, irContext);
    if (arrayElementType->isPointerType()) {
        auto irArrayPointerType = irGenerator->generateIrArrayPointerType((IRPointerType*)arrayElementType);
        irArrayPointerType->setValue(this->generateTypeValue(irArrayPointerType, irGenerator));
        return irArrayPointerType;
    }
    auto irArrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateIrPointerType(arrayElementType));
    irArrayPointerType->setValue(this->generateTypeValue(irArrayPointerType, irGenerator));
    return irArrayPointerType;
}

IRInstructionNode* ArrayTypeSignatureIRStrategy::generateTypeValue(IRArrayPointerType* irType, IRGenerator* irGenerator) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
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
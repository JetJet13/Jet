//
// Created by Johny Georges on 2024-06-17.
//

#include "array-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRArrayPointerType> ArrayTypeSignatureIRStrategy::generate(std::shared_ptr<ArrayTypeSignature> arrayTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto arrayElementType = irGenerator->generateTypeFor(arrayTypeSignature->getElementType(), scope, irContext);
    auto irArrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateIrPointerType(arrayElementType));
    irArrayPointerType->setValue(this->generateTypeValue(irArrayPointerType, irGenerator, irContext));
    return irArrayPointerType;
}

IRTypeValueInstructionNode* ArrayTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRArrayPointerType> irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            allocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}
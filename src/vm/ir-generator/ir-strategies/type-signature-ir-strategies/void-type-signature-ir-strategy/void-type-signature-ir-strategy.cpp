//
// Created by Johny Georges on 2026-01-10.
//

#include "void-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRType> VoidTypeSignatureIRStrategy::generate(std::shared_ptr<IRGenerator> irGenerator) {
    auto irVoidType = std::make_shared<IRType>(irGenerator->getVoidType());
    irVoidType->setValue(this->generateTypeValue(irVoidType, irGenerator));
    return irVoidType;
}

std::shared_ptr<IRTypeValueInstructionNode> VoidTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRType> irType, std::shared_ptr<IRGenerator> irGenerator) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.VOID),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(0),
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
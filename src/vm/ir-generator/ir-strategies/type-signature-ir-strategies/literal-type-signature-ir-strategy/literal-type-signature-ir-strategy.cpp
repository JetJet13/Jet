//
// Created by Johny Georges on 2024-07-10.
//

#include "literal-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRType* LiteralTypeSignatureIRStrategy::generate(LiteralTypeSignature* literalTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    if (literalTypeSignature->typeSourceIs(INT_LITERAL_TYPE_SOURCE)) {
        auto irType = new IRType(llvm::IntegerType::get(**irContext->getContext(), 32));
        irType->setValue(this->generateTypeValue(irType, irGenerator));
        return irType;
    } else if (literalTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
        auto irType = new IRType(irGenerator->generateFloatType());
        irType->setValue(this->generateTypeValue(irType, irGenerator));
        return irType;
    } else if (literalTypeSignature->typeSourceIs(CHAR_LITERAL_TYPE_SOURCE)) {
        auto irType = new IRType(llvm::IntegerType::get(**irContext->getContext(), 8));
        irType->setValue(this->generateTypeValue(irType, irGenerator));
        return irType;
    } else if (literalTypeSignature->typeSourceIs(BOOL_LITERAL_TYPE_SOURCE)) {
        auto irType = new IRType(llvm::IntegerType::get(**irContext->getContext(), 1));
        irType->setValue(this->generateTypeValue(irType, irGenerator));
        return irType;
    } else if (literalTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto charType = llvm::IntegerType::get(**irContext->getContext(), 8);
        auto irCharType = new IRType(charType);
        irCharType->setValue(this->generateTypeValue(irCharType, irGenerator));
        auto irType = irGenerator->generateIrArrayPointerType(irCharType);
        irType->setValue(this->generateTypeValue(irType, irGenerator));
        return irType;
    } else {
        return new IRType(irGenerator->generateLiteralType());
    }
}

IRInstructionNode* LiteralTypeSignatureIRStrategy::generateTypeValue(IRType* irType, IRGenerator* irGenerator) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = this->generateInitialTypeValue(irType, irTypeValueType, irGenerator);
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return new IRInstructionNode(
        allocation,
        irGenerator->generateIrPointerType(irTypeValueType),
        {},
        { storeInstruction }
    );
}

llvm::Value* LiteralTypeSignatureIRStrategy::generateInitialTypeValue(IRType* irType, IRTypeValueType* irTypeValueType, IRGenerator* irGenerator) {
    auto pointerType = irGenerator->generatePointerType();
    if (irType->isIntegerType()) {
        return llvm::ConstantStruct::get(irTypeValueType->getType(), {
                irGenerator->generateIntConstant(IR_TYPE_ID.INT),
                irGenerator->generateIntConstant(irType->getSizeInBytes()),
                irGenerator->generateIntConstant(0),
                llvm::ConstantPointerNull::get(pointerType)
        });
    } else if (irType->isFloatType()) {
        return llvm::ConstantStruct::get(irTypeValueType->getType(), {
                irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT),
                irGenerator->generateIntConstant(irType->getSizeInBytes()),
                irGenerator->generateIntConstant(0),
                llvm::ConstantPointerNull::get(pointerType)
        });
    } else if (irType->isCharType()) {
        return llvm::ConstantStruct::get(irTypeValueType->getType(), {
                irGenerator->generateIntConstant(IR_TYPE_ID.CHAR),
                irGenerator->generateIntConstant(irType->getSizeInBytes()),
                irGenerator->generateIntConstant(0),
                llvm::ConstantPointerNull::get(pointerType)
        });
    } else if (irType->isBoolType()) {
        return llvm::ConstantStruct::get(irTypeValueType->getType(), {
                irGenerator->generateIntConstant(IR_TYPE_ID.BOOL),
                irGenerator->generateIntConstant(irType->getSizeInBytes()),
                irGenerator->generateIntConstant(0),
                llvm::ConstantPointerNull::get(pointerType)
        });
    } else {
        return llvm::ConstantStruct::get(irTypeValueType->getType(), {
                irGenerator->generateIntConstant(IR_TYPE_ID.STRING),
                irGenerator->generateIntConstant(irType->getSizeInBytes()),
                irGenerator->generateIntConstant(0),
                llvm::ConstantPointerNull::get(pointerType)
        });
    }
}
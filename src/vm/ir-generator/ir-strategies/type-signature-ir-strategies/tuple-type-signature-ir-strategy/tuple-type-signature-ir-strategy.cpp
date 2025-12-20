//
// Created by Johny Georges on 2024-07-11.
//

#include "tuple-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

IRStructRefType* TupleTypeSignatureIRStrategy::generate(TupleTypeSignature* tupleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto tupleElementTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (int i = 0; i < tupleTypeSignature->size(); ++i) {
        auto tupleElement = tupleTypeSignature->getTypeSignatureAtIndex(i);
        auto tupleElementIrType = irGenerator->generateTypeFor(tupleElement, scope, irContext);
        tupleElementTypes.push_back(tupleElementIrType->getType());
        auto key = std::to_string(i);
        keyIndexMap.insert(std::pair(key, i));
        keyTypeMap.insert(std::pair(key, tupleElementIrType));
    }

    auto structType = new IRStructType(llvm::StructType::get(**irContext->getContext(), tupleElementTypes), keyIndexMap, keyTypeMap);
    structType->setAlignmentAndSizeForIRTypes();
    structType->setKeyId(tupleTypeSignature->getKeyId());
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    auto structRefType = irGenerator->generateIRStructRefType(structType);
    structRefType->setValue(irGenerator->generateIRTypeValueFor(structRefType, irContext));
    return structRefType;
}

IRTypeValueInstructionNode* TupleTypeSignatureIRStrategy::generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(irType->size()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            irType->hasKeyId()
            ? irGenerator->getOrInsertGlobalVariableString(irType->getKeyId(), irType->getKeyId(), irContext)
            : llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}
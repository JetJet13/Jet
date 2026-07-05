//
// Created by Johny Georges on 2024-07-11.
//

#include "struct-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

std::shared_ptr<IRStructRefType> StructTypeSignatureIRStrategy::generate(std::shared_ptr<StructTypeSignature> structTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIdMap = std::unordered_map<unsigned long, std::string>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : structTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        auto index = structTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first);
        structPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(std::pair(keyValue.first, index));
        keyIdMap.insert(std::pair(index, keyValue.first));
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto structType = std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), structPropertyTypes), keyIndexMap, keyIdMap, keyTypeMap);
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    auto structRefType = irGenerator->generateIRStructRefType(structType);
    structRefType->setValue(this->generateTypeValue(structRefType, irGenerator, irContext));
    return structRefType;
}

IRTypeValueInstructionNode* StructTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRStructType> irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(irType->size()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}

IRTypeValueInstructionNode* StructTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRStructRefType> irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}
//
// Created by Johny Georges on 2025-07-04.
//

#include "interface-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../types/ir-type-id.h"

IRStructType* InterfaceTypeSignatureIRStrategy::generate(InterfaceTypeSignature* interfaceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {

    auto interfacePropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : interfaceTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        interfacePropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(keyValue.first, interfaceTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto structType = new IRStructType(llvm::StructType::create(**irContext->getContext(), interfacePropertyTypes, interfaceTypeSignature->getId()), keyIndexMap, keyTypeMap);
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    return structType;
}

IRTypeValueInstructionNode* InterfaceTypeSignatureIRStrategy::generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
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
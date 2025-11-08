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
    structType->setId(interfaceTypeSignature->getId());
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    return structType;
}

IRInstructionNode* InterfaceTypeSignatureIRStrategy::generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto keys = std::vector<llvm::Constant*>();
    auto keyTypes = std::vector<llvm::Type*>();
    for (int i = 0; i < irType->size(); ++i) {
        auto key = irType->getKeyForIndex(i);
        auto keyAsValue = irGenerator->generateRawString(key);
        keys.push_back(keyAsValue);
        keyTypes.push_back(keyAsValue->getType());
    }
    auto structKeysType = llvm::ConstantStruct::get(llvm::StructType::get(**irContext->getContext(), keyTypes), keys);
    auto structKeysVariable = irContext->getModule()->getOrInsertGlobal(
            irType->getId(),
            structKeysType->getType(),
            [irContext, structKeysType, irType]() -> llvm::GlobalVariable* {
                return new llvm::GlobalVariable(
                        *irContext->getModule(),
                        structKeysType->getType(),
                        true,
                        llvm::GlobalValue::InternalLinkage,
                        structKeysType,
                        irType->getId()
                );
            }
    );
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(irType->size()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            structKeysVariable
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            {},
            { storeInstruction }
    );
}
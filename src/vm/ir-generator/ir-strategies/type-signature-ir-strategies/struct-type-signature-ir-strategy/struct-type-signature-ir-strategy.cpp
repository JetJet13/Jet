//
// Created by Johny Georges on 2024-07-11.
//

#include "struct-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

IRStructType* StructTypeSignatureIRStrategy::generate(StructTypeSignature* structTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    std::string id;
    for (auto keyValue : structTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        structPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
            std::pair(keyValue.first, structTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
        id += "_" + keyValue.first + "$" + irType->getId();
    }
    auto structType = new IRStructType(llvm::StructType::get(**irContext->getContext(), structPropertyTypes), keyIndexMap, keyTypeMap);
    structType->setId("struct." + MD5().operator()(id));
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    return structType;
}

IRInstructionNode* StructTypeSignatureIRStrategy::generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
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
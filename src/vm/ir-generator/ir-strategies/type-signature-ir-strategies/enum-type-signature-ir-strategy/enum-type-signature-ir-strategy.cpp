//
// Created by Johny Georges on 2024-07-11.
//

#include "enum-type-signature-ir-strategy.h"

IRPointerType* EnumTypeSignatureIRStrategy::generate(EnumTypeSignature* enumTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    return irGenerator->generatePointerType();
}

IREnumType* EnumTypeSignatureIRStrategy::generate(EnumTypeSignature* enumTypeSignature, std::vector<llvm::Constant*> enumValues, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto enumPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (int i = 0; i < enumTypeSignature->getKeyValuePairs()->size(); ++i) {
        auto enumPropertyType = irGenerator->generateTypeFor(enumValues[i]);
        enumPropertyTypes.push_back(enumPropertyType->getType());
        auto enumKey = enumTypeSignature->getKeyValuePairs()->getKeyValues()[i].first;
        keyIndexMap.insert(std::pair(enumKey, i));
        keyTypeMap.insert(std::pair(enumKey, enumPropertyType));
    }

    return new IREnumType(llvm::StructType::get(**context, enumPropertyTypes), keyIndexMap, keyTypeMap);
}
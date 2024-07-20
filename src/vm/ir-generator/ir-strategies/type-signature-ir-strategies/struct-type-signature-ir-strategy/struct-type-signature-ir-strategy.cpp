//
// Created by Johny Georges on 2024-07-11.
//

#include "struct-type-signature-ir-strategy.h"

IRType* StructTypeSignatureIRStrategy::generate(StructTypeSignature* structTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    for (auto keyValue : structTypeSignature->getKeyValuePairs()->getKeyValues()) {
        structPropertyTypes.push_back(
                irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature())->getType()
        );
        keyIndexMap.insert(
            std::pair(keyValue.first, structTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first))
        );
    }
    return new IRStructType(llvm::StructType::get(**context, structPropertyTypes), keyIndexMap);
}
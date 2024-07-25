//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"

IRStructType* ClassTypeSignatureIRStrategy::generate(ClassTypeSignature* classTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature());
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(keyValue.first, classTypeSignature->getProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    return new IRStructType(llvm::StructType::get(**context, classPropertyTypes), keyIndexMap, keyTypeMap);
}
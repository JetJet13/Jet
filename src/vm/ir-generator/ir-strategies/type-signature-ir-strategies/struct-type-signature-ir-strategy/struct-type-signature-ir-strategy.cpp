//
// Created by Johny Georges on 2024-07-11.
//

#include "struct-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRStructType* StructTypeSignatureIRStrategy::generate(StructTypeSignature* structTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : structTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature());
        Logger::log("keyValue", keyValue.first, keyValue.second->toString(), keyValue.second->getTargetTypeSignature()->toString());
        structPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
            std::pair(keyValue.first, structTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    Logger::log("return ir struct type");
    return new IRStructType(llvm::StructType::get(**context, structPropertyTypes), keyIndexMap, keyTypeMap);
}
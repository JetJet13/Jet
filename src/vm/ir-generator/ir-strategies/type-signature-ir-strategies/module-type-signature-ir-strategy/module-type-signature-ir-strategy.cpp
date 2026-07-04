//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature-ir-strategy.h"


IRModuleType* ModuleTypeSignatureIRStrategy::generate(std::shared_ptr<ModuleTypeSignature> moduleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto moduleExportTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyIdMap = std::unordered_map<unsigned long, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : moduleTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature(), scope, irContext);
        auto index = moduleTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first);
        moduleExportTypes.push_back(irType->getType());
        keyIndexMap.insert(std::pair(keyValue.first, index));
        keyIdMap.insert(std::pair(index, keyValue.first));
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }

    return new IRModuleType(llvm::StructType::get(**irContext->getContext(), moduleExportTypes), keyIndexMap, keyIdMap, keyTypeMap);
}
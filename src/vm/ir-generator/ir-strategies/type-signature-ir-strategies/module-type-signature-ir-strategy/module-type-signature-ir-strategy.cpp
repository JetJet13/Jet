//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature-ir-strategy.h"


IRModuleType* ModuleTypeSignatureIRStrategy::generate(ModuleTypeSignature* moduleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto moduleExportTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : moduleTypeSignature->getKeyValuePairs()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getTargetTypeSignature(), scope, irContext);
        moduleExportTypes.push_back(irType->getType());
        keyIndexMap.insert(
            std::pair(keyValue.first, moduleTypeSignature->getKeyValuePairs()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }

    return new IRModuleType(llvm::StructType::get(**irContext->getContext(), moduleExportTypes), keyIndexMap, keyTypeMap);
}
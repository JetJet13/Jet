// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-07-11.
//

#include "enum-type-signature-ir-strategy.h"

std::shared_ptr<IRType> EnumTypeSignatureIRStrategy::generate(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return irGenerator->generateTypeFor(enumTypeSignature->getType(), scope, irContext);
}

std::shared_ptr<IREnumType> EnumTypeSignatureIRStrategy::generate(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::vector<llvm::Constant*> enumValues, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto enumPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, uint64_t>();
    auto keyIdMap = std::unordered_map<uint64_t, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (uint64_t i = 0; i < enumTypeSignature->getKeyValuePairs()->size(); ++i) {
        auto enumPropertyType = irGenerator->generateTypeFor(enumValues[i]);
        enumPropertyTypes.push_back(enumPropertyType->getType());
        auto enumKey = enumTypeSignature->getKeyValuePairs()->getKeyValues()[i].first;
        keyIndexMap.insert(std::pair(enumKey, i));
        keyIdMap.insert(std::pair(i, enumKey));
        keyTypeMap.insert(std::pair(enumKey, enumPropertyType));
    }

    auto irType = std::make_shared<IREnumType>(llvm::StructType::get(**irContext->getContext(), enumPropertyTypes), keyIndexMap, keyIdMap, keyTypeMap);
    irType->setId(enumTypeSignature->getId());
    return irType;
}
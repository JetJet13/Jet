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
// Created by Johny Georges on 2024-12-31.
//

#include "new-class-instance-type-signature-ir-strategy.h"

std::shared_ptr<IRNewClassInstanceType> NewClassInstanceTypeSignatureIRStrategy::generate(std::shared_ptr<NewClassInstanceTypeSignature> newClassInstanceTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, uint64_t>();
    auto keyIdMap = std::unordered_map<uint64_t, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : newClassInstanceTypeSignature->getClassTypeSignature()->getInstanceProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        auto index = newClassInstanceTypeSignature->getClassTypeSignature()->getInstanceProperties()->findKeyIndex(keyValue.first);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(std::pair(keyValue.first, index));
        keyIdMap.insert(std::pair(index, newClassInstanceTypeSignature->getClassTypeSignature()->stripClassNameFromKey(keyValue.first)));
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto classInstanceProperties = std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyIdMap, keyTypeMap);
    classInstanceProperties->setAlignmentAndSizeForIRTypes();
    classInstanceProperties->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstanceProperties->setValue(irGenerator->generateIRTypeValueFor(classInstanceProperties, irContext));
    auto classInstancePropertiesPointerType = irGenerator->generateIRStructRefType(classInstanceProperties);
    classInstancePropertiesPointerType->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstancePropertiesPointerType->setValue(irGenerator->generateIRTypeValueFor(classInstancePropertiesPointerType, irContext));

    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(newClassInstanceTypeSignature->getClassTypeSignature()->getModuleId(), newClassInstanceTypeSignature->getClassTypeSignature()->getId()).value());
    auto irType = std::make_shared<IRNewClassInstanceType>(
        irClassType,
        newClassInstanceTypeSignature->getConstructorId(),
        classInstancePropertiesPointerType
    );
    irType->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    return irType;
}
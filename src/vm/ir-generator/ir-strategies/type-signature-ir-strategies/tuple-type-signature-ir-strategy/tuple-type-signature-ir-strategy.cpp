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

#include "tuple-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

std::shared_ptr<IRStructRefType> TupleTypeSignatureIRStrategy::generate(std::shared_ptr<TupleTypeSignature> tupleTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto tupleElementTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, uint64_t>();
    auto keyIdMap = std::unordered_map<uint64_t, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (uint64_t i = 0; i < tupleTypeSignature->size(); ++i) {
        auto tupleElement = tupleTypeSignature->getTypeSignatureAtIndex(i);
        auto tupleElementIrType = irGenerator->generateTypeFor(tupleElement, scope, irContext);
        tupleElementTypes.push_back(tupleElementIrType->getType());
        auto key = std::to_string(i);
        keyIndexMap.insert(std::pair(key, i));
        keyIdMap.insert(std::pair(i, key));
        keyTypeMap.insert(std::pair(key, tupleElementIrType));
    }

    auto structType = std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), tupleElementTypes), keyIndexMap, keyIdMap, keyTypeMap);
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(irGenerator->generateIRTypeValueFor(structType, irContext));
    auto structRefType = irGenerator->generateIRStructRefType(structType);
    structRefType->setValue(irGenerator->generateIRTypeValueFor(structRefType, irContext));
    return structRefType;
}
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
// Created by Johny Georges on 2025-11-21.
//

#include "lambda-scope-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRStructType> LambdaScopeTypeSignatureIRStrategy::generate(std::shared_ptr<LambdaScopeTypeSignature> lambdaScopeTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, uint64_t>();
    auto keyIdMap = std::unordered_map<uint64_t, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    auto capturedVariableIds = lambdaScopeTypeSignature->getCapturedVariableIds();
    int i = 0;
    for (auto capturedVariableId : *capturedVariableIds) {
        auto irVariableType = scope->find(capturedVariableId).value()->getIRType()->getSourceType();
        auto irCapturedVariableType = irGenerator->generateIRCapturedVariableType(irVariableType);
        irCapturedVariableType->setValue(this->generateTypeValue(irCapturedVariableType, irGenerator, irContext));
        structPropertyTypes.push_back(irCapturedVariableType->getType());
        keyIndexMap.insert(std::pair(capturedVariableId, i));
        keyIdMap.insert(std::pair(i, capturedVariableId));
        keyTypeMap.insert(std::pair(capturedVariableId, irCapturedVariableType));
        i++;
    }
    auto structType = std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), structPropertyTypes), keyIndexMap, keyIdMap, keyTypeMap);
    structType->setValue(irGenerator->generateIRTypeValueFor(structType, irContext));
    return structType;
}

std::shared_ptr<IRTypeValueInstructionNode> LambdaScopeTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRCapturedVariableType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.CAPTURED_VARIABLE),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return std::make_shared<IRTypeValueInstructionNode>(
            allocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}
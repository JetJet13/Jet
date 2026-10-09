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
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRStructExpressionNode> StructExpressionIRStrategy::generate(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getStructTypeSignature(), scope, irContext);
    auto structValues = std::vector<std::shared_ptr<IRExpressionNode>>();
    auto structValueSourceAllocationMap = std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irContext, irOperation);
        irNode->markAsAssigned();
        structValues.push_back(irNode);
        if (irNode->getSourceAllocation()) {
            structValueSourceAllocationMap.insert(
                std::pair(keyValuePair->getKey()->getId() , irNode->getSourceAllocation().value())
            );
        }
    }
    auto structAllocation = this->generateStructAllocation(irType->getStructIRType(), structValueSourceAllocationMap, irGenerator, irContext);
    auto structRefAllocation = this->generateStructRefAllocation(node, irType, irGenerator, irContext, irOperation);
    structRefAllocation->setParentAllocation(structAllocation);
    return std::make_shared<IRStructExpressionNode>(
            node,
            structRefAllocation,
            irGenerator->generateArcAllocation(irContext),
            irType,
            structValues
    );
}

std::shared_ptr<IRInstructionNode> StructExpressionIRStrategy::generateStructAllocation(std::shared_ptr<IRStructType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> structValueSourceAllocationMap, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(irType->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irType),
            {},
            std::move(structValueSourceAllocationMap)
    );
}

std::shared_ptr<IRInstructionNode> StructExpressionIRStrategy::generateStructRefAllocation(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRStructRefType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}
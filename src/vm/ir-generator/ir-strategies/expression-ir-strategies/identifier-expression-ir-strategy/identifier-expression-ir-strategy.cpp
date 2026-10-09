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
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRExpressionNode> IdentifierExpressionIRStrategy::generate(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto allocation = scope->findAcrossScopes(node->getIdentifierNode()->getId());
    if (!allocation && node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        allocation = scope->findAcrossScopes(FunctionIdGenerator::generateFor(node->getIdentifierNode()->getId(), invocableTypeSignature));
    }

    if (irOperation->isCopy() && allocation.value()->getIRType()->getSourceType()->requiresArc()) {
        return std::make_shared<IRIdentifierExpressionNode>(node, allocation.value(), irGenerator->generateArcAllocation(irContext));
    }
    return std::make_shared<IRIdentifierExpressionNode>(node, allocation.value(), scope->findArc(node->getIdentifierNode()->getId()));
}
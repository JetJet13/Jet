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
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-access-expression-node.h"

std::shared_ptr<IRExpressionNode> ClassPropertyAccessExpressionIRStrategy::generate(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = std::dynamic_pointer_cast<IRStructRefType>(classScope->getIRType()->getUnderlyingType());
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto targetKey = node->getPropertyName();
    if (node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irType);
        auto classTypeSignature = node->getPropertyAccess()->getClassAccess()->getClassTypeSignature();
        auto methodId = classTypeSignature->addClassNameToKey(FunctionIdGenerator::generateFor(targetKey, invocableTypeSignature));
        auto irMethod = scope->findAcrossScopes(methodId);
        return std::make_shared<IRClassMethodAccessExpressionNode>(node, irMethod.value(), irInvocableType);
    }
    auto targetIndex = sourceType->getStructIRType()->getIndexForKey(targetKey);
    return std::make_shared<IRClassPropertyAccessExpressionNode>(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType);
}
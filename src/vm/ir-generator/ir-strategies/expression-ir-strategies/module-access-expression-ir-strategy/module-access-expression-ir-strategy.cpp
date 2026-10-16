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
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-ir-strategy.h"
#include "../../../../../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"

std::shared_ptr<IRExpressionNode> ModuleAccessExpressionIRStrategy::generate(std::shared_ptr<ASTModuleAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto sourceValue = scope->findGlobalVariable(node->getModuleName(), node->getModuleTargetName());
    if (!sourceValue && node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        auto lambdaValueName = FunctionIdGenerator::generateFor(node->getModuleTargetName(), invocableTypeSignature);
        sourceValue = scope->findGlobalVariable(node->getModuleId(), lambdaValueName);
    }

    return std::make_shared<IRModuleAccessExpressionNode>(node, sourceValue.value()->getValue(), sourceValue.value()->getIRType());
}
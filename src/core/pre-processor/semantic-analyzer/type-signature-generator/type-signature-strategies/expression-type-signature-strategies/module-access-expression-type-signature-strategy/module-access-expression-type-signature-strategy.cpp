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
// Created by Johny Georges on 2024-11-07.
//

#include "module-access-expression-type-signature-strategy.h"
#include "../../../../types/function-id-generator/function-id-generator.h"

void ModuleAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = scope->find(moduleAccessExpression->getModuleName(), moduleAccessExpression->getModuleTargetName());
    if (typeSignature->isUnknown() && context->getTypeSignature() && context->getTypeSignature().value()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(context->getTypeSignature().value());
        auto functionTypeSignature = scope->findGlobalFunction(moduleAccessExpression->getModuleId(), moduleAccessExpression->getModuleTargetName(), FunctionIdGenerator::generateFor(invocableTypeSignature));
        if (functionTypeSignature) {
            moduleAccessExpression->setTypeSignature(functionTypeSignature.value()->convertToVariableTypeSignature());
            return;
        }
    }
    moduleAccessExpression->setTypeSignature(typeSignature);
}
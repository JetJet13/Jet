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
// Created by Johny Georges on 2024-05-07.
//

#include "class-method-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ClassMethodInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTClassMethodInvocationExpressionNode> classMethodInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classMethodInvocationExpression->getArguments(), context, scope);
    auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(scope->find(classMethodInvocationExpression->getClassAccess()->getThis()->getId()));
    auto methodName = classMethodInvocationExpression->getName()->getId();
    auto methodId = FunctionIdGenerator::generateFor(methodName, classMethodInvocationExpression->getArguments()->getArgumentListTypeSignature()->toDetailString());
    auto classMethodTypeSignature = classTypeSignature->getInstanceMethods()->find(methodId);
    if (!classMethodTypeSignature) {
        classMethodInvocationExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }

    classMethodInvocationExpression->getName()->setTypeSignature(classMethodTypeSignature.value());
    auto classMethodReturnType = (classMethodTypeSignature.value())->getReturnType();
    classMethodInvocationExpression->setTypeSignature(classMethodReturnType);
}
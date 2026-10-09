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
// Created by Johny Georges on 2024-05-08.
//

#include "curry-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"

void CurryExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTCurryExpressionNode> curryExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(curryExpression->getCallableExpression(), context, scope);
    for (auto argument : *curryExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), context);
    }

    if (curryExpression->getCallableExpression()->getTypeSignature()->typeSourceIs(FUNCTION_INVOCATION_TYPE_SOURCE)) {
        auto functionInvocationTypeSignature = std::dynamic_pointer_cast<FunctionInvocationTypeSignature>(curryExpression->getCallableExpression()->getTypeSignature());
        curryExpression->setTypeSignature(functionInvocationTypeSignature->getReturnType()->getTargetTypeSignature());
        return;
    }

    curryExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
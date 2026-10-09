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

#include "function-return-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionReturnExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionReturnExpressionNode> functionReturnExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    if (functionReturnExpression->getExpression()) {
        strategyMap->assignTypeSignatureFor(functionReturnExpression->getExpression().value(), context, scope);
        functionReturnExpression->setTypeSignature(functionReturnExpression->getExpression().value()->getTypeSignature());
    } else {
        functionReturnExpression->setTypeSignature(std::make_shared<VoidTypeSignature>());
    }
}
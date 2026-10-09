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
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"


void ConcatExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTConcatExpressionNode> concatExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(concatExpression->getLeftNode(), context, scope);
    strategyMap->assignTypeSignatureFor(concatExpression->getRightNode(), context, scope);
    auto leftTypeSignature = concatExpression->getLeftNode()->getTypeSignature();
    auto rightTypeSignature = concatExpression->getRightNode()->getTypeSignature();

    if (leftTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(leftTypeSignature->getTargetTypeSignature());
        leftTypeSignature = sharedTypeSignature->getUnderlyingType();
    }

    if (rightTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(rightTypeSignature->getTargetTypeSignature());
        rightTypeSignature = sharedTypeSignature->getUnderlyingType();
    }


    if (leftTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    if (leftTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    concatExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}

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

#include "array-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void ArrayAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getIndex()->getIndex(), context, scope);

    if (arrayAccessExpression->getSource()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(arrayAccessExpression->getSource()->getTypeSignature()->getTargetTypeSignature());
        if (sharedTypeSignature->getUnderlyingType()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
            auto arrayTypeSignature = std::dynamic_pointer_cast<ArrayTypeSignature>(sharedTypeSignature->getUnderlyingType()->getTargetTypeSignature());
            arrayAccessExpression->setTypeSignature(arrayTypeSignature->getElementType());
            return;
        }
        arrayAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }

    if (arrayAccessExpression->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        arrayAccessExpression->setTypeSignature((std::dynamic_pointer_cast<ArrayTypeSignature>(arrayAccessExpression->getSource()->getTypeSignature()->getTargetTypeSignature())->getElementType()));
        return;
    }

    arrayAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
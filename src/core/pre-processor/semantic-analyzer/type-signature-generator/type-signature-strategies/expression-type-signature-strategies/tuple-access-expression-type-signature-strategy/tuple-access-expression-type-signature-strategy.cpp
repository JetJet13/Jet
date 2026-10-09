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
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void TupleAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessExpression->getSource()->getSource(), context, scope);
    auto sourceTypeSignature = tupleAccessExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (sourceTypeSignature->typeTargetIs(TUPLE_TYPE_SOURCE)) {
        auto tupleTypeSignature = std::dynamic_pointer_cast<TupleTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        tupleAccessExpression->setTypeSignature(tupleTypeSignature->getTypeSignatureAtIndex(tupleAccessExpression->getIndex()->getIndexValue()));
        return;
    }

    tupleAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
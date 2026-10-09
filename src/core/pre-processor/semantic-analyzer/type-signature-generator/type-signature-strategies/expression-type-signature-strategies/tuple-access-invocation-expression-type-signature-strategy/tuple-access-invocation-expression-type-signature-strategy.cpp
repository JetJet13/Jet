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
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void TupleAccessInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> tupleAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getSource()->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getArguments(), context, scope);

    auto sourceTypeSignature = tupleAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature();
    if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
        sourceTypeSignature = (std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature)->getUnderlyingType());
    }

    if (sourceTypeSignature->typeSourceIs(TUPLE_TYPE_SOURCE)) {
        strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getObjectAccess(), context, scope);
        auto tupleSource = std::dynamic_pointer_cast<TupleTypeSignature>(sourceTypeSignature);
        auto functionTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(tupleSource->getTypeSignatureAtIndex(
                tupleAccessInvocationExpression->getIndex()->getIndexValue()
        ));
        tupleAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        tupleAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    }
    tupleAccessInvocationExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}
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
// Created by Johny Georges on 2024-05-23.
//

#include "for-in-statement-type-signature-strategy.h"
#include "../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void ForInStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTForInStatementNode> forStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(forStatementNode->getSource()->getSource(), context, scope);
    forStatementNode->getSource()->setTypeSignature(
            forStatementNode
                    ->getSource()
                    ->getSource()
                    ->getTypeSignature()
                    ->getTargetTypeSignature()
    );

    if (forStatementNode->getSource()->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        auto arrayTypeSignature = std::dynamic_pointer_cast<ArrayTypeSignature>(forStatementNode->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature());
        forStatementNode->getVariable()->getVariable()->setTypeSignature(arrayTypeSignature->getElementType());
    } else if (forStatementNode->getSource()->getSource()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(forStatementNode->getSource()->getSource()->getTypeSignature()->getTargetTypeSignature());
        if (sharedTypeSignature->getUnderlyingType()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
            auto arrayTypeSignature = std::dynamic_pointer_cast<ArrayTypeSignature>(sharedTypeSignature->getUnderlyingType()->getTargetTypeSignature());
            forStatementNode->getVariable()->getVariable()->setTypeSignature(arrayTypeSignature->getElementType());
        } else {
            forStatementNode->getVariable()->getVariable()->setTypeSignature(std::make_shared<UnknownTypeSignature>());
        }
    } else {
        forStatementNode->getVariable()->getVariable()->setTypeSignature(std::make_shared<UnknownTypeSignature>());
    }
    forStatementNode->getVariable()->setTypeSignature(
        forStatementNode->getVariable()->getVariable()->getTypeSignature()
    );
    scope->insert(forStatementNode->getVariable()->getVariable()->getId(), forStatementNode->getVariable()->getTypeSignature());
    strategyMap->assignTypeSignatureFor(forStatementNode->getBlock(), context, scope);
}
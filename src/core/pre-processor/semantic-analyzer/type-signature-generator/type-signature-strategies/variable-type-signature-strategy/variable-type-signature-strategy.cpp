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
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"
#include "../../../types/function-id-generator/function-id-generator.h"

void VariableTypeSignatureStrategy::assignAndAddToScope(std::shared_ptr<ASTVariableDeclarationNode> variableDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto variableContext = std::make_shared<VariableContext>();
    if (variableDeclaration->isConst()) {
        variableContext->markAsConstant();
    }

    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        strategyMap->assignTypeSignatureFor(variableDeclaration->getVarInitNode()->getTypeNode().value(), context, scope);
        variableDeclaration->setTypeSignature(variableDeclaration->getVarInitNode()->getTypeNode().value()->getTypeSignature()->convertToVariableTypeSignature());

        if (variableDeclaration->isGlobal()) {
            scope->insertGlobal(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
            scope->insertGlobalVariableContext(variableDeclaration->getId(), variableContext);
        } else {
            scope->insert(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
            scope->insertVariableContext(variableDeclaration->getId(), variableContext);
        }
        strategyMap->assignTypeSignatureFor(variableDeclaration->getInitializerNode(), context, scope);
        return;
    }

    strategyMap->assignTypeSignatureFor(variableDeclaration->getInitializerNode(), context, scope);
    variableDeclaration->setTypeSignature(variableDeclaration->getInitializerNode()->getTypeSignature()->convertToVariableTypeSignature());

    if (variableDeclaration->isGlobal()) {
        scope->insertGlobal(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
        scope->insertGlobalVariableContext(variableDeclaration->getId(), variableContext);
    } else {
        scope->insert(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
        scope->insertVariableContext(variableDeclaration->getId(), variableContext);
    }
}
//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

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
//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature-strategy.h"

void ModuleTypeSignatureStrategy::assign(ASTModuleDeclarationNode* moduleDeclarationNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto exportedNode : *moduleDeclarationNode->getExports()) {
        moduleDeclarationNode->getTypeSignature()->addKeyValuePair(exportedNode->getId(), scope->find(exportedNode->getId()));
    }
}

void ModuleTypeSignatureStrategy::assignInitial(ASTModuleDeclarationNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    node->setTypeSignature(new ModuleTypeSignature());
}
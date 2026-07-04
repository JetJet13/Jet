//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature-strategy.h"

void ModuleTypeSignatureStrategy::assign(std::shared_ptr<ASTModuleDeclarationNode> moduleDeclarationNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    moduleDeclarationNode->getTypeSignature()->setId(moduleDeclarationNode->getId());
    for (auto exportedNode : *moduleDeclarationNode->getExports()) {
        moduleDeclarationNode->getModuleTypeSignature()->addKeyValuePair(exportedNode->getId(), scope->find(exportedNode->getId()));
    }
}
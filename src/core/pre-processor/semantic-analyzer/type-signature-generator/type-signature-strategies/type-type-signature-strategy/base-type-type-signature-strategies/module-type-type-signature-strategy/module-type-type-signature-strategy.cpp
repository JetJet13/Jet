//
// Created by Johny Georges on 2026-05-30.
//

#include "module-type-type-signature-strategy.h"

void ModuleTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTModuleTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = scope->find(node->getModuleName(), node->getModuleTargetName());
    node->setTypeSignature(typeSignature);
}
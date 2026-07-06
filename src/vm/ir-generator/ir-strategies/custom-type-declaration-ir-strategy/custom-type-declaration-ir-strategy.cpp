//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-ir-strategy.h"

std::shared_ptr<IRCustomTypeDeclarationNode> CustomTypeDeclarationIRStrategy::generate(std::shared_ptr<ASTCustomTypeDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irType->isStructType()) {
        auto structType = std::dynamic_pointer_cast<IRStructType>(irType);
        structType->makeGlobal(node->getId(), irContext->getContext());
    }
    scope->insert(node->getId(), irType);
    return std::make_shared<IRCustomTypeDeclarationNode>(node, irType);
}
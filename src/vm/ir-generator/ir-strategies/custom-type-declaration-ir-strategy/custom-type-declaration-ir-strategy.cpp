//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-ir-strategy.h"

IRCustomTypeDeclarationNode* CustomTypeDeclarationIRStrategy::generate(std::shared_ptr<ASTCustomTypeDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irType->isStructType()) {
        auto structType = (IRStructType*)irType;
        structType->makeGlobal(node->getId(), irContext->getContext());
    }
    scope->insert(node->getId(), irType);
    return new IRCustomTypeDeclarationNode(node, irType);
}
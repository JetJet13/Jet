//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

IRCustomTypeDeclarationNode* CustomTypeDeclarationIRStrategy::generate(ASTCustomTypeDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irType->isStructType()) {
        auto structType = (IRStructType*)irType;
        structType->makeGlobal(node->getId(), irContext->getContext());
    }
    scope->insert(node->getId(), irType);
    return new IRCustomTypeDeclarationNode(node, irType);
}
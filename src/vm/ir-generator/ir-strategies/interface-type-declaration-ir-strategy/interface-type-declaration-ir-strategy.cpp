//
// Created by Johny Georges on 2025-07-04.
//

#include "interface-type-declaration-ir-strategy.h"

IRInterfaceTypeDeclarationNode* InterfaceTypeDeclarationIRStrategy::generate(std::shared_ptr<ASTInterfaceTypeDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irType = irGenerator->generateTypeFor(node->getInterfaceTypeSignature(), scope, irContext);
    scope->insert(node->getName()->getId(), irType);
    return new IRInterfaceTypeDeclarationNode(node, irType);
}
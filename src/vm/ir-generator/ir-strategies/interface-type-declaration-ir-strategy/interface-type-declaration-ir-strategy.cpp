//
// Created by Johny Georges on 2025-07-04.
//

#include "interface-type-declaration-ir-strategy.h"

std::shared_ptr<IRInterfaceTypeDeclarationNode> InterfaceTypeDeclarationIRStrategy::generate(std::shared_ptr<ASTInterfaceTypeDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irType = irGenerator->generateTypeFor(node->getInterfaceTypeSignature(), scope, irContext);
    scope->insert(node->getName()->getId(), irType);
    return std::make_shared<IRInterfaceTypeDeclarationNode>(node, irType);
}
//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

void InterfaceTypeDeclarationIdStrategy::assign(ASTNode* node) {
    auto interfaceTypeDeclarationNode = (ASTInterfaceTypeDeclarationNode*)node;
    interfaceTypeDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    interfaceTypeDeclarationNode
                            ->getName()
                            ->getLexeme()
                            ->getToken()
                            ->getValueId()
                            .value()
            )
    );
}
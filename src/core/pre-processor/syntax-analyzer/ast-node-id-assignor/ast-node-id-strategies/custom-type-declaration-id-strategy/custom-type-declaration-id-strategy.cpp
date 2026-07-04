//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

void CustomTypeDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto customTypeDeclarationNode = std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node);
    customTypeDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    customTypeDeclarationNode
                            ->getName()
                            ->getLexeme()
                            ->getToken()
                            ->getValueId()
                            .value()
            )
    );
}
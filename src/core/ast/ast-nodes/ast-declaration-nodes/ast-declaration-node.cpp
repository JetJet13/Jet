//
// Created by Johny Georges on 2024-05-01.
//

#include "ast-declaration-node.h"


DeclarationId* ASTDeclarationNode::getId() {
    return _id;
}

void ASTDeclarationNode::setId(DeclarationId* id) {
    _id = id;
}
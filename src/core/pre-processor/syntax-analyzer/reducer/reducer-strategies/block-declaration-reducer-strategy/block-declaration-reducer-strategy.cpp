//
// Created by Johny Georges on 2024-03-14.
//

#include "block-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-block-declaration-node.h"

ASTNode* BlockDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto blockNode = (ASTBlockNode*)nodes[0];
    return new ASTBlockDeclarationNode(blockNode->getContents());
}
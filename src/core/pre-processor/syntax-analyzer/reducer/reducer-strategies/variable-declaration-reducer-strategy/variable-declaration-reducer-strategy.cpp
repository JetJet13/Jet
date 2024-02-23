//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"

ASTNode* VariableDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTVariableDeclarationNode(
            (ASTVariableInitNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}

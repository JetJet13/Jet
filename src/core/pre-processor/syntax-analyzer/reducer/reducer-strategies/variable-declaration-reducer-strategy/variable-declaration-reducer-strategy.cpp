//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"

ASTNode* VariableDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var declaration since nodes list is not 2");
    }
    auto expression = (ASTExpressionNode*)nodes[1];
    return new ASTVariableDeclarationNode(
            (ASTVariableInitNode*)nodes[0],
            expression
    );
}

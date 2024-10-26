//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"

ASTNode* VariableDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to var declaration since nodes list is not 2 or 3");
    }

    if (nodes.size() == 2) {
        return new ASTVariableDeclarationNode(
                (ASTVariableInitNode*)nodes[0],
                (ASTExpressionNode*)nodes[1]
        );
    } else {
        return new ASTVariableDeclarationNode(
                (ASTVariableInitNode*)nodes[1],
                (ASTExpressionNode*)nodes[2],
                (ASTExportNode*)nodes[0]
        );
    }
}

//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-init-node.h"

ASTNode* VariableInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to var init node since nodes list is not 3");
    }

    return new ASTVariableInitNode(
            (ASTVariableTypeNode*)nodes[0],
            (ASTIdentifierNode*)nodes[1]
    );
}

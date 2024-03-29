//
// Created by Johny Georges on 2024-03-29.
//

#include "for-variable-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-variable-node.h"

ASTNode* ForVariableReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for variable since nodes list is not 1");
    }

    return new ASTForVariableNode(
            (ASTIdentifierExpressionNode*)nodes[0]
    );
}
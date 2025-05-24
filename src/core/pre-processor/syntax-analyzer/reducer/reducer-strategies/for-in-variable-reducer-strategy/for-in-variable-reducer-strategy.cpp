//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-variable-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-in-variable-node.h"

ASTNode* ForInVariableReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for variable since nodes list is not 1");
    }

    return new ASTForInVariableNode(
            (ASTIdentifierExpressionNode*)nodes[0]
    );
}
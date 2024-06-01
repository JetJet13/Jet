//
// Created by Johny Georges on 2024-03-28.
//

#include "if-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-block-node.h"

ASTNode* IfBlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to if block since nodes list is not of size 3");
    }

    return new ASTIfBlockNode(
            (ASTIfNode*)nodes[0],
            (ASTControlFlowConditionNode*)nodes[1],
            (ASTControlFlowBlockNode*)nodes[2]
    );
}
//
// Created by Johny Georges on 2024-03-28.
//

#include "else-if-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-if-block-node.h"

ASTNode* ElseIfBlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to else if block since nodes list is not of size 3");
    }

    return new ASTElseIfBlockNode(
            (ASTControlFlowConditionNode*)nodes[1],
            (ASTControlFlowBlockNode*)nodes[2]
    );
}
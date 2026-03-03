//
// Created by Johny Georges on 2026-03-02.
//

#include "binary-comparator-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

ASTNode* BinaryComparatorExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to binary comparator expression since nodes list is too short");
    }
    return new ASTBinaryComparatorExpressionNode(
            (ASTExpressionNode*)nodes[0],
            (ASTBinaryComparatorOperatorNode*)nodes[1],
            (ASTExpressionNode*)nodes[2]
    );
}
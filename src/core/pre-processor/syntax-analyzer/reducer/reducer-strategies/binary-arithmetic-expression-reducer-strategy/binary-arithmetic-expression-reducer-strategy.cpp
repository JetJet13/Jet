//
// Created by Johny Georges on 2024-02-19.
//

#include "binary-arithmetic-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

ASTNode* BinaryArithmeticExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to binary arithmetic expression since nodes list is too short");
    }
    return new ASTBinaryArithmeticExpressionNode(
            (ASTExpressionNode*)nodes[0],
            (ASTBinaryArithmeticOperatorNode*)nodes[1],
            (ASTExpressionNode*)nodes[2]
    );
}
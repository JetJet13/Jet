//
// Created by Johny Georges on 2024-02-19.
//

#include "binary-arithmetic-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

std::shared_ptr<ASTNode> BinaryArithmeticExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to binary arithmetic expression since nodes list is too short");
    }
    return std::make_shared<ASTBinaryArithmeticExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTBinaryArithmeticOperatorNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2])
    );
}
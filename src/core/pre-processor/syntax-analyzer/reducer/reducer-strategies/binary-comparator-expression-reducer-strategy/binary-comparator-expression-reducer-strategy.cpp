//
// Created by Johny Georges on 2026-03-02.
//

#include "binary-comparator-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

std::shared_ptr<ASTNode> BinaryComparatorExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to binary comparator expression since nodes list is too short");
    }
    return std::make_shared<ASTBinaryComparatorExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTBinaryComparatorOperatorNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2])
    );
}
//
// Created by Johny Georges on 2024-03-20.
//

#include "function-parameter-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"

std::shared_ptr<ASTNode> FunctionParameterReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to function parameter since nodes list is not of size 3");
    }

    return std::make_shared<ASTFunctionParameterNode>(
            std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
    );
}
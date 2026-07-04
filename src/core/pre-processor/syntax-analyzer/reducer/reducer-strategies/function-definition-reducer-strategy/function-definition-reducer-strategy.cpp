//
// Created by Johny Georges on 2024-10-25.
//

#include "function-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-definition-node.h"

std::shared_ptr<ASTNode> FunctionDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to function definition since nodes list is not of size 5");
    }

    return std::make_shared<ASTFunctionDefinitionNode>(
            std::dynamic_pointer_cast<ASTFunctionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionNameNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[4])
    );
}
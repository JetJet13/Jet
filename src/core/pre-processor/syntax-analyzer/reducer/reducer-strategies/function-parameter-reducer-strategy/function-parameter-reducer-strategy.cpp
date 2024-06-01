//
// Created by Johny Georges on 2024-03-20.
//

#include "function-parameter-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"

ASTNode* FunctionParameterReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to function parameter since nodes list is not of size 3");
    }

    return new ASTFunctionParameterNode(
            (ASTIdentifierExpressionNode*)nodes[0],
            (ASTColonNode*)nodes[1],
            (ASTTypeNode*)nodes[2]
    );
}
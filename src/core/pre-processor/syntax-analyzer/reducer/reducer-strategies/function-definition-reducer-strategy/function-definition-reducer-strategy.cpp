//
// Created by Johny Georges on 2024-10-25.
//

#include "function-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-definition-node.h"

ASTNode* FunctionDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to function definition since nodes list is not of size 4");
    }

    return new ASTFunctionDefinitionNode(
            (ASTFunctionNode*)nodes[0],
            (ASTFunctionNameNode*)nodes[1],
            (ASTFunctionParameterListNode*)nodes[2],
            (ASTTypeNode*)nodes[3]
    );
}
//
// Created by Johny Georges on 2024-03-18.
//

#include "function-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

ASTNode* FunctionDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to function declaration since nodes list is not of size 4");
    }

    return new ASTFunctionDeclarationNode(
            (ASTIdentifierExpressionNode*)nodes[1],
            (ASTFunctionParameterListNode*)nodes[2],
            (ASTBlockNode*)nodes[3]
    );
}
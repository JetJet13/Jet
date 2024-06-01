//
// Created by Johny Georges on 2024-04-06.
//

#include "lambda-function-type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-lambda-nodes/ast-function-lambda-type-parameter-list-node.h"

ASTNode* LambdaFunctionTypeParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to lambda procedure type parameter list since nodes list is not of size 2");
    }

    return new ASTFunctionLambdaTypeParameterListNode(
            (ASTFunctionNode*)nodes[0],
            (ASTTypeParameterListNode*)nodes[1]
    );
}
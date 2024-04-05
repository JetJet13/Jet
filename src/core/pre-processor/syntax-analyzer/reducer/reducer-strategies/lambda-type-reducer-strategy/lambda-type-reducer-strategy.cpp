//
// Created by Johny Georges on 2024-04-04.
//

#include "lambda-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-node.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* LambdaTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to lambda type since nodes list is not of size 3");
    }

    return ASTTypeNodeFactory::createLambdaTypeNode(
            new ASTLambdaTypeNode(
                (ASTLambdaTypeParameterListNode*)nodes[0],
                (ASTTypeNode*)nodes[2]
    ));
}
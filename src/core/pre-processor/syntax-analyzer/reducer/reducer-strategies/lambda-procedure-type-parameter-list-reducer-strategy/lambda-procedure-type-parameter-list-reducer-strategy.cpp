//
// Created by Johny Georges on 2024-04-06.
//

#include "lambda-procedure-type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-lambda-nodes/ast-procedure-lambda-type-parameter-list-node.h"

ASTNode* LambdaProcedureTypeParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to lambda procedure type parameter list since nodes list is not of size 2");
    }

    return new ASTProcedureLambdaTypeParameterListNode(
            (ASTProcedureNode*)nodes[0],
            (ASTTypeParameterListNode*)nodes[1]
    );
}
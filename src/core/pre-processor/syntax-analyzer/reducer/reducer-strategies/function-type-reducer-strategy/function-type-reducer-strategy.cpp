//
// Created by Johny Georges on 2024-05-31.
//

#include "function-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* FunctionTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return ASTTypeNodeFactory::createFunctionTypeNode(
        new ASTFunctionTypeNode(
            (ASTFunctionLambdaTypeParameterListNode*)nodes[0],
            (ASTLambdaTypeFatArrowNode*)nodes[1],
            (ASTTypeNode*)nodes[2]
    ));
}
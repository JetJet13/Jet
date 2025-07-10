//
// Created by Johny Georges on 2025-07-09.
//

#include "lambda-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-node.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* LambdaTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return ASTTypeNodeFactory::createLambdaTypeNode(
            new ASTLambdaTypeNode(
                    (ASTLambdaTypeParameterListNode*)nodes[0],
                    (ASTLambdaTypeFatArrowNode*)nodes[1],
                    (ASTTypeNode*)nodes[2]
            ));
}
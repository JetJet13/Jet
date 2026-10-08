//
// Created by Johny Georges on 2025-07-09.
//

#include "lambda-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-node.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> LambdaTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return ASTTypeNodeFactory::createLambdaTypeNode(
            std::make_shared<ASTLambdaTypeNode>(
                    std::dynamic_pointer_cast<ASTLambdaTypeParameterListNode>(nodes[0]),
                    std::dynamic_pointer_cast<ASTLambdaArrowNode>(nodes[1]),
                    std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
            ));
}
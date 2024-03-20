//
// Created by Johny Georges on 2024-03-19.
//

#include "function-return-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"

ASTNode* FunctionReturnExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTFunctionReturnExpressionNode(this->createExpressionNode(nodes[1]));
}
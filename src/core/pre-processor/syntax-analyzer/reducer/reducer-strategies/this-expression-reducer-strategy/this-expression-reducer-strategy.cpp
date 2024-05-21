//
// Created by Johny Georges on 2024-05-20.
//

#include "this-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

ASTNode* ThisExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTThisExpressionNode(
            (ASTThisNode*)nodes[0]
    );
}
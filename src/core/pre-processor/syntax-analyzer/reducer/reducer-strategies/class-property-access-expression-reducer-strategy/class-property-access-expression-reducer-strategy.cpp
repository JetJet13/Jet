//
// Created by Johny Georges on 2024-04-27.
//

#include "class-property-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"

ASTNode* ClassPropertyAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTClassPropertyAccessExpressionNode(
            (ASTClassPropertyAccessNode*)nodes[0]
    );
}
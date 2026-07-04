//
// Created by Johny Georges on 2024-04-27.
//

#include "class-property-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"

std::shared_ptr<ASTNode> ClassPropertyAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTClassPropertyAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTClassPropertyAccessNode>(nodes[0])
    );
}
//
// Created by Johny Georges on 2024-05-20.
//

#include "this-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

std::shared_ptr<ASTNode> ThisExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTThisExpressionNode>(
            std::dynamic_pointer_cast<ASTThisNode>(nodes[0])
    );
}
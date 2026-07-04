//
// Created by Johny Georges on 2024-04-25.
//

#include "class-method-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"

std::shared_ptr<ASTNode> ClassMethodInvocationExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class method invocation expression since nodes list is not of size 3");
    }

    return std::make_shared<ASTClassMethodInvocationExpressionNode>(
            std::dynamic_pointer_cast<ASTClassAccessNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTClassMethodCallNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[2])
    );
}
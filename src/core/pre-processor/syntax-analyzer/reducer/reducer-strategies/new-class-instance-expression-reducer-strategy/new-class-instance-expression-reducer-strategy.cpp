//
// Created by Johny Georges on 2024-04-26.
//

#include "new-class-instance-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"


std::shared_ptr<ASTNode> NewClassInstanceExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to new class instance expression since nodes list is not of size 3");
    }

    if (nodes.at(1)->is(AST_CLASS_NAME_NODE)) {
        return std::make_shared<ASTNewClassInstanceExpressionNode>(
                std::dynamic_pointer_cast<ASTNewNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTClassNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[2])
        );
    }
    return std::make_shared<ASTNewClassInstanceExpressionNode>(
            std::dynamic_pointer_cast<ASTNewNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[2])
    );
}
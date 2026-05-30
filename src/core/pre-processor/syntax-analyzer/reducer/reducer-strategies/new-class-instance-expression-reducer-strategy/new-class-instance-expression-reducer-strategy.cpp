//
// Created by Johny Georges on 2024-04-26.
//

#include "new-class-instance-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"


ASTNode* NewClassInstanceExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to new class instance expression since nodes list is not of size 3");
    }

    if (nodes.at(1)->is(AST_CLASS_NAME_NODE)) {
        return new ASTNewClassInstanceExpressionNode(
                (ASTNewNode*)nodes[0],
                (ASTClassNameNode*)nodes[1],
                (ASTFunctionArgumentListNode*)nodes[2]
        );
    }
    return new ASTNewClassInstanceExpressionNode(
            (ASTNewNode*)nodes[0],
            (ASTModuleAccessExpressionNode*)nodes[1],
            (ASTFunctionArgumentListNode*)nodes[2]
    );
}
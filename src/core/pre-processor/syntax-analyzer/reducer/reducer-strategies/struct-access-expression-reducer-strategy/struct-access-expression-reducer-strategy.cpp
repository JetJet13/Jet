//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-access-expression-node.h"

ASTNode* StructAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to struct access expression since nodes list is too short");
    }

    return new ASTStructAccessExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTIdentifierExpressionNode*)this->createExpressionNode(nodes[2])
    );
}
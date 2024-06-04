//
// Created by Johny Georges on 2024-03-12.
//

#include "array-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"

ASTNode* ArrayAccessReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1 || !nodes[0]->is(AST_ARRAY_NODE)) {
        throw std::invalid_argument("unable to reduce to array access node since node list != 1 or nodes[0] is not an instance of array base node");
    }
    auto arrayNode = (ASTArrayNode*)nodes[0];
    if (!arrayNode->getFirstElement()) {
        throw std::invalid_argument("unable to reduce to array access node since array base node has no elements");
    }
    auto index = (ASTExpressionNode*)(arrayNode->getFirstElement().value());
    return new ASTArrayAccessNode(arrayNode->getLeftBracket(), index, arrayNode->getRightBracket());
}
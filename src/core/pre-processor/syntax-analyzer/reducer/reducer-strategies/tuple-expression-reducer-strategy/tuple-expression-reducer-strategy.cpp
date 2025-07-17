//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"

ASTNode* TupleExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto tupleExpression = new ASTTupleExpressionNode(
            (ASTTupleListStartNode*)nodes[0],
            (ASTTupleListEndNode*)nodes[nodes.size() - 1]
    );
    for (int i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TUPLE_ITEM_NODE)) {
            tupleExpression->addItem((ASTTupleItemNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            tupleExpression->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to tuple expression since node list is malformed");
        }
    }

    return tupleExpression;
}
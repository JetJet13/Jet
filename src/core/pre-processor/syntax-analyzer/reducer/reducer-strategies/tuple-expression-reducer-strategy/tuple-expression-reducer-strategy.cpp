//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"

std::shared_ptr<ASTNode> TupleExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto tupleExpression = std::make_shared<ASTTupleExpressionNode>(
            std::dynamic_pointer_cast<ASTTupleListStartNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTTupleListEndNode>(nodes[nodes.size() - 1])
    );
    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TUPLE_ITEM_NODE)) {
            tupleExpression->addItem(std::dynamic_pointer_cast<ASTTupleItemNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            tupleExpression->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to tuple expression since node list is malformed");
        }
    }

    return tupleExpression;
}
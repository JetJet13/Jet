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
    for (auto node : nodes) {
        if (node->is(AST_TUPLE_ITEM_NODE)) {
            tupleExpression->addItem((ASTTupleItemNode*)node);
        }

        if (node->is(AST_COMMA_NODE)) {
            tupleExpression->addComma((ASTCommaNode*)node);
        }
    }
    return tupleExpression;
}
//
// Created by Johny Georges on 2024-04-09.
//

#include "tuple-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> TupleTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto tupleTypeNode = std::make_shared<ASTTupleTypeNode>(
            std::dynamic_pointer_cast<ASTTupleTypeStartNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTTupleTypeEndNode>(nodes[nodes.size() - 1])
    );

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_TYPE_NODE)) {
            tupleTypeNode->addValueType(std::dynamic_pointer_cast<ASTTypeNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            tupleTypeNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to tuple type since node list is malformed");
        }
    }

    return ASTTypeNodeFactory::createTupleTypeNode(tupleTypeNode);
}
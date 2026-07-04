//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-struct-type-nodes/ast-struct-type-node.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> StructTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto structTypeNode = std::make_shared<ASTStructTypeNode>(
            std::dynamic_pointer_cast<ASTStructTypeStartNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTStructTypeEndNode>(nodes[nodes.size() - 1])
    );

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_STRUCT_TYPE_KEY_NODE)) {
            structTypeNode->addKeyValueType(std::dynamic_pointer_cast<ASTStructTypeKeyValueNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            structTypeNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to struct type since node list is malformed");
        }
    }

    return ASTTypeNodeFactory::createStructTypeNode(structTypeNode);
}
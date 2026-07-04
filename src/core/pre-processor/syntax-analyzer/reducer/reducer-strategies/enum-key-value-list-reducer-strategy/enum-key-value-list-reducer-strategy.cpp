//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-value-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-list-node.h"

std::shared_ptr<ASTNode> EnumKeyValueListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto enumKeyValueListNode = std::make_shared<ASTEnumKeyValueListNode>(std::dynamic_pointer_cast<ASTEnumKeyValueListStartNode>(nodes[0]), std::dynamic_pointer_cast<ASTEnumKeyValueListEndNode>(nodes[nodes.size() - 1]));
    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_ENUM_KEY_VALUE_NODE)) {
            enumKeyValueListNode->addEnumKeyValue(std::dynamic_pointer_cast<ASTEnumKeyValueNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            enumKeyValueListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to enum key value list since node list is malformed");
        }
    }
    return enumKeyValueListNode;
}
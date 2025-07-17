//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-value-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-list-node.h"

ASTNode* EnumKeyValueListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto enumKeyValueListNode = new ASTEnumKeyValueListNode((ASTEnumKeyValueListStartNode*)nodes[0], (ASTEnumKeyValueListEndNode*)nodes[nodes.size() - 1]);
    for (int i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_ENUM_KEY_VALUE_NODE)) {
            enumKeyValueListNode->addEnumKeyValue((ASTEnumKeyValueNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            enumKeyValueListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to enum key value list since node list is malformed");
        }
    }
    return enumKeyValueListNode;
}
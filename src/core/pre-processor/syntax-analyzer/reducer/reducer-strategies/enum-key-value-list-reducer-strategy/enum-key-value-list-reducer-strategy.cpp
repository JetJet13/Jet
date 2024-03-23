//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-value-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-list-node.h"

ASTNode* EnumKeyValueListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto enumKeyValueListNode = new ASTEnumKeyValueListNode();
    for (auto node : nodes) {
        if (node->is(AST_ENUM_KEY_VALUE_NODE)) {
            enumKeyValueListNode->addEnumKeyValue((ASTEnumKeyValueNode*)node);
        }
    }
    return enumKeyValueListNode;
}
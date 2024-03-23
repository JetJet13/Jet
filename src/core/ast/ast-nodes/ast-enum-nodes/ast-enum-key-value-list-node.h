//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H
#define JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-enum-key-value-node.h"


class ASTEnumKeyValueListNode : public ASTNode {
private:
    std::vector<ASTEnumKeyValueNode*> _enumKeyValues;
public:
    ASTEnumKeyValueListNode();
    ASTEnumKeyValueListNode(std::vector<ASTEnumKeyValueNode*> enumKeyValues);
    std::vector<ASTEnumKeyValueNode*> getParameters();
    unsigned long numParameters();
    ASTEnumKeyValueListNode* addEnumKeyValue(ASTEnumKeyValueNode* enumKeyValue);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H

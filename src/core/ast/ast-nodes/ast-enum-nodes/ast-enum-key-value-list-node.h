//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H
#define JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-enum-key-value-node.h"
#include "ast-enum-key-value-list-start-node.h"
#include "ast-enum-key-value-list-end-node.h"


class ASTEnumKeyValueListNode : public ASTNode {
private:
    ASTEnumKeyValueListStartNode* _enumKeyValueListStartNode;
    ASTEnumKeyValueListEndNode* _enumKeyValueListEndNode;
    std::vector<ASTEnumKeyValueNode*> _enumKeyValues;
public:
    ASTEnumKeyValueListNode(ASTEnumKeyValueListStartNode* enumKeyValueListStartNode, ASTEnumKeyValueListEndNode* enumKeyValueListEndNode);
    ASTEnumKeyValueListNode(ASTEnumKeyValueListStartNode* enumKeyValueListStartNode, std::vector<ASTEnumKeyValueNode*> enumKeyValues, ASTEnumKeyValueListEndNode* enumKeyValueListEndNode);
    std::vector<ASTEnumKeyValueNode*> getParameters();
    unsigned long numParameters();
    ASTEnumKeyValueListNode* addEnumKeyValue(ASTEnumKeyValueNode* enumKeyValue);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H

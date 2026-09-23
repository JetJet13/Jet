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
#include "../ast-comma-node.h"

class ASTEnumKeyValueListNode : public ASTNode {
private:
    std::shared_ptr<ASTEnumKeyValueListStartNode> _enumKeyValueListStartNode;
    std::shared_ptr<ASTEnumKeyValueListEndNode> _enumKeyValueListEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTEnumKeyValueNode>> _enumKeyValues;
public:
    ASTEnumKeyValueListNode(std::shared_ptr<ASTEnumKeyValueListStartNode> enumKeyValueListStartNode, std::shared_ptr<ASTEnumKeyValueListEndNode> enumKeyValueListEndNode);
    ASTEnumKeyValueListNode(std::shared_ptr<ASTEnumKeyValueListStartNode> enumKeyValueListStartNode, std::vector<std::shared_ptr<ASTEnumKeyValueNode>> enumKeyValues, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTEnumKeyValueListEndNode> enumKeyValueListEndNode);
    std::vector<std::shared_ptr<ASTEnumKeyValueNode>> getParameters();
    uint64_t numParameters();
    std::shared_ptr<ASTEnumKeyValueListNode> addEnumKeyValue(std::shared_ptr<ASTEnumKeyValueNode> enumKeyValue);
    std::shared_ptr<ASTEnumKeyValueListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_LIST_NODE_H

//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_STRUCT_EXPRESSION_NODE_H
#define JETLANG_AST_STRUCT_EXPRESSION_NODE_H

#include <unordered_map>
#include "../ast-node.h"
#include "ast-expression-node.h"
#include "../ast-struct-nodes/ast-struct-key-value-node.h"

class ASTStructExpressionNode : public ASTExpressionNode {
private:
    std::vector<ASTStructKeyValueNode*> _keyValuePairs;
public:
    ASTStructExpressionNode();
    ASTStructExpressionNode(std::vector<ASTStructKeyValueNode*> keyValuePairs);
    std::vector<ASTStructKeyValueNode*> getKeyValuePairs();
    ASTStructExpressionNode* addKeyValuePair(ASTStructKeyValueNode* keyValuePair);
    unsigned long size();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_EXPRESSION_NODE_H

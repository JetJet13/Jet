//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_STRUCT_KEY_VALUE_NODE_H
#define JETLANG_AST_STRUCT_KEY_VALUE_NODE_H

#include <string>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-colon-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTStructKeyValueNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _key;
    ASTColonNode* _colon;
    ASTExpressionNode* _value;
public:
    ASTStructKeyValueNode(ASTIdentifierExpressionNode* key, ASTColonNode* colon, ASTExpressionNode* value);
    ASTIdentifierExpressionNode* getKey();
    ASTExpressionNode* getValue();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_KEY_VALUE_NODE_H

//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_STRUCT_KEY_VALUE_NODE_H
#define JETLANG_AST_STRUCT_KEY_VALUE_NODE_H

#include <string>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "ast-struct-colon-node.h"

class ASTStructKeyValueNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierExpressionNode> _key;
    std::shared_ptr<ASTStructColonNode> _colon;
    std::shared_ptr<ASTExpressionNode> _value;
public:
    ASTStructKeyValueNode(std::shared_ptr<ASTIdentifierExpressionNode> key, std::shared_ptr<ASTStructColonNode> colon, std::shared_ptr<ASTExpressionNode> value);
    std::shared_ptr<ASTIdentifierExpressionNode> getKey();
    std::shared_ptr<ASTExpressionNode> getValue();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_KEY_VALUE_NODE_H

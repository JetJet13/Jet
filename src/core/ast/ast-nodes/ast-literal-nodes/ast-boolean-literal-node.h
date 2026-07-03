//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BOOLEAN_LITERAL_NODE_H
#define JETLANG_AST_BOOLEAN_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "../../../lexeme/lexeme.h"
#include "ast-literal-node.h"

class ASTBooleanLiteralNode : public ASTLiteralNode {
    using ASTLiteralNode::ASTLiteralNode;
private:
    bool _value;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void setValue(std::shared_ptr<TokenTable> tokenTable) override;
    bool getValue();
};

#endif //JETLANG_AST_BOOLEAN_LITERAL_NODE_H

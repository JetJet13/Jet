//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_FLOAT_LITERAL_NODE_H
#define JETLANG_AST_FLOAT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTFloatLiteralNode : public ASTLiteralNode {
    using ASTLiteralNode::ASTLiteralNode;
private:
    std::string _value;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void setValue(std::shared_ptr<TokenTable> tokenTable) override;
    std::string getValue();
};

#endif //JETLANG_AST_FLOAT_LITERAL_NODE_H

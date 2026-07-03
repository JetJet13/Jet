//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_INT_LITERAL_NODE_H
#define JETLANG_AST_INT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTIntLiteralNode : public ASTLiteralNode {
    using ASTLiteralNode::ASTLiteralNode;
private:
    std::string _value;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void setValue(std::shared_ptr<TokenTable> tokenTable) override;
    std::string getValue();
};

#endif //JETLANG_AST_INT_LITERAL_NODE_H

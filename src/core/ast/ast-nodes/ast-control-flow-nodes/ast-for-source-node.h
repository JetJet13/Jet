//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_SOURCE_NODE_H
#define JETLANG_AST_FOR_SOURCE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTForSourceNode : public ASTNode {
private:
    ASTExpressionNode* _source;
public:
    ASTForSourceNode(ASTExpressionNode* source);
    ASTExpressionNode* getSource();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FOR_SOURCE_NODE_H

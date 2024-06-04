//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_THIS_EXPRESSION_NODE_H
#define JETLANG_AST_THIS_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"
#include "../ast-class-nodes/ast-this-node.h"

class ASTThisExpressionNode : public ASTExpressionNode {
private:
    ASTThisNode* _this;
public:
    ASTThisExpressionNode(ASTThisNode* thisNode);
    ASTThisNode* getThisNode();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_THIS_EXPRESSION_NODE_H

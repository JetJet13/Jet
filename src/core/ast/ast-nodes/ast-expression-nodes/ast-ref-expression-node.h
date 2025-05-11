//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_REF_EXPRESSION_NODE_H
#define JETLANG_AST_REF_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-ref-node.h"
#include "../../../type-signature/ref-type-signature/ref-type-signature.h"

class ASTRefExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _expression;
    ASTRefNode* _refNode;
    RefTypeSignature* _typeSignature = new RefTypeSignature();
public:
    ASTRefExpressionNode(ASTRefNode* refNode, ASTExpressionNode* astExpressionNode);
    ASTExpressionNode* getExpressionNode();
    ASTRefNode* getRefNode();
    void markAsReferenced() override;
    RefTypeSignature* getTypeSignature() override;
    void setTypeSignature(RefTypeSignature* typeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_EXPRESSION_NODE_H

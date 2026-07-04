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
    std::shared_ptr<ASTExpressionNode> _expression;
    std::shared_ptr<ASTRefNode> _refNode;
    std::shared_ptr<RefTypeSignature> _typeSignature = std::make_shared<RefTypeSignature>();
public:
    ASTRefExpressionNode(std::shared_ptr<ASTRefNode> refNode, std::shared_ptr<ASTExpressionNode> astExpressionNode);
    std::shared_ptr<ASTExpressionNode> getExpressionNode();
    std::shared_ptr<ASTRefNode> getRefNode();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<RefTypeSignature> getRefTypeSignature();
    void setTypeSignature(std::shared_ptr<RefTypeSignature> typeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_EXPRESSION_NODE_H

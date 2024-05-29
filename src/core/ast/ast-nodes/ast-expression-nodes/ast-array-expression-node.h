//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_ARRAY_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_EXPRESSION_NODE_H

#include <vector>
#include <string>
#include "../ast-node.h"
#include "ast-expression-node.h"
#include "../../../type-signature/array-type-signature/array-type-signature.h"

class ASTArrayExpressionNode : public ASTExpressionNode {
private:
    std::vector<ASTExpressionNode*>* _elements;
    ArrayTypeSignature* _typeSignature = new ArrayTypeSignature();
public:
    explicit ASTArrayExpressionNode();
    explicit ASTArrayExpressionNode(std::vector<ASTExpressionNode*> elements);
    explicit ASTArrayExpressionNode(std::vector<ASTExpressionNode*>* elements);
    std::vector<ASTExpressionNode*>* getElements();
    ASTArrayExpressionNode* addElement(ASTExpressionNode* element);
    ArrayTypeSignature* getTypeSignature() override;
    void setTypeSignature(ArrayTypeSignature* arrayTypeSignature);
    unsigned long size();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ARRAY_EXPRESSION_NODE_H

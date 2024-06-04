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
#include "../ast-array-nodes/ast-array-node.h"

class ASTArrayExpressionNode : public ASTExpressionNode {
private:
    ASTArrayNode* _array;
    ArrayTypeSignature* _typeSignature = new ArrayTypeSignature();
public:
    explicit ASTArrayExpressionNode(ASTArrayNode* array);
    ASTArrayNode* getArray();
    std::vector<ASTExpressionNode*>* getElements();
    ASTArrayExpressionNode* addElement(ASTExpressionNode* element);
    ArrayTypeSignature* getTypeSignature() override;
    void setTypeSignature(ArrayTypeSignature* arrayTypeSignature);
    unsigned long size();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_EXPRESSION_NODE_H

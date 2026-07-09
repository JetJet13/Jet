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
    std::shared_ptr<ASTArrayNode> _array;
    std::shared_ptr<ArrayTypeSignature> _typeSignature = std::make_shared<ArrayTypeSignature>();
public:
    explicit ASTArrayExpressionNode(std::shared_ptr<ASTArrayNode> array);
    std::shared_ptr<ASTArrayNode> getArray();
    std::vector<std::shared_ptr<ASTExpressionNode>>* getElements();
    std::shared_ptr<ASTArrayExpressionNode> addElement(std::shared_ptr<ASTExpressionNode> element);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<ArrayTypeSignature> getArrayTypeSignature();
    void setTypeSignature(std::shared_ptr<ArrayTypeSignature> arrayTypeSignature);
    unsigned long size();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_EXPRESSION_NODE_H

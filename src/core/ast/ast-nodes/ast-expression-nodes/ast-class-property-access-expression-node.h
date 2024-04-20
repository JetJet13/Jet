//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "ast-array-expression-node.h"
#include "../ast-array-nodes/ast-array-access-node.h"
#include "../ast-class-nodes/ast-class-property-access-node.h"

class ASTClassPropertyAccessExpressionNode : public ASTExpressionNode {
private:
    ASTClassPropertyAccessNode* _propertyAccess;
public:
    ASTClassPropertyAccessExpressionNode(ASTClassPropertyAccessNode* propertyAccess);
    ASTClassPropertyAccessNode* getPropertyAccess();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H

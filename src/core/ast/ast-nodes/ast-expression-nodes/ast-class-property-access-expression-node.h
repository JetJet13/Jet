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
    std::shared_ptr<ASTClassPropertyAccessNode> _propertyAccess;
public:
    ASTClassPropertyAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessNode> propertyAccess);
    std::shared_ptr<ASTClassPropertyAccessNode> getPropertyAccess();
    std::string getPropertyName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H

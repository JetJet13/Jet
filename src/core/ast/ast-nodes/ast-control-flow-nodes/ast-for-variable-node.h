//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_VARIABLE_NODE_H
#define JETLANG_AST_FOR_VARIABLE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTForVariableNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _variable;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    ASTForVariableNode(ASTIdentifierExpressionNode* variable);
    ASTIdentifierExpressionNode* getVariable();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FOR_VARIABLE_NODE_H

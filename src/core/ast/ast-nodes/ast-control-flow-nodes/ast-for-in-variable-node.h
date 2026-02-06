//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_IN_VARIABLE_NODE_H
#define JETLANG_AST_FOR_IN_VARIABLE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTForInVariableNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _variable;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
    bool _isReferenced = false;
    unsigned long _captureCount = 0;
public:
    ASTForInVariableNode(ASTIdentifierExpressionNode* variable);
    void markAsReferenced();
    void markAsCaptured();
    unsigned long getCaptureCount();
    bool isReferenced();
    bool isCaptured();
    ASTIdentifierExpressionNode* getVariable();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FOR_IN_VARIABLE_NODE_H

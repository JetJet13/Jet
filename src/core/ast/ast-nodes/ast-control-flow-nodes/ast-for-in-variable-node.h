//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_IN_VARIABLE_NODE_H
#define JETLANG_AST_FOR_IN_VARIABLE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTForInVariableNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierExpressionNode> _variable;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
    unsigned long _captureCount = 0;
public:
    ASTForInVariableNode(std::shared_ptr<ASTIdentifierExpressionNode> variable);
    void markAsCaptured();
    unsigned long getCaptureCount();
    bool isCaptured();
    std::shared_ptr<ASTIdentifierExpressionNode> getVariable();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FOR_IN_VARIABLE_NODE_H

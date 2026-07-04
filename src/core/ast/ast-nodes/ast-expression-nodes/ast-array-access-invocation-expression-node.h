//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "ast-array-access-expression-node.h"
#include "../../../type-signature/invocable-type-signature/invocable-type-signature.h"

class ASTArrayAccessInvocationExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTArrayAccessExpressionNode> _arrayAccess;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
public:
    ASTArrayAccessInvocationExpressionNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccess, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::shared_ptr<ASTArrayAccessExpressionNode> getArrayAccess();
    std::shared_ptr<ASTExpressionNode> getSource();
    std::shared_ptr<ASTArrayAccessNode> getIndex();
    std::shared_ptr<InvocableTypeSignature> getInvocableTypeSignature();
    unsigned long numArguments();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

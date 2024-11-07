//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"
#include "ast-callable-expression-node.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"


class ASTFunctionInvocationExpressionNode : public ASTCallableExpressionNode {
private:
    ASTExpressionNode* _function;
    ASTFunctionArgumentListNode* _arguments;
    FunctionInvocationTypeSignature* _typeSignature = new FunctionInvocationTypeSignature();
public:
    explicit ASTFunctionInvocationExpressionNode(ASTExpressionNode* function, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTExpressionNode* getFunction();
    unsigned long numArguments();
    void setTypeSignature(FunctionInvocationTypeSignature* functionInvocationTypeSignature);
    FunctionInvocationTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H

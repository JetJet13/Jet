//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"
#include "ast-callable-expression-node.h"
#include "../ast-class-nodes/ast-class-method-call-node.h"

class ASTClassMethodInvocationExpressionNode : public ASTCallableExpressionNode {
private:
    ASTClassMethodCallNode* _method;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTClassMethodInvocationExpressionNode(ASTClassMethodCallNode* name, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTClassMethodCallNode* getName();
    unsigned long numArguments();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"

class ASTFunctionInvocationExpressionNode : public ASTExpressionNode {
private:
    ASTFunctionCallNode* _function;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTFunctionInvocationExpressionNode(ASTFunctionCallNode* name, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTFunctionCallNode* getName();
    unsigned long numArguments();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H

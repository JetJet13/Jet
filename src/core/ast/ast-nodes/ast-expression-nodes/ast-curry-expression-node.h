//
// Created by Johny Georges on 2024-04-05.
//

#ifndef JETLANG_AST_CURRY_EXPRESSION_NODE_H
#define JETLANG_AST_CURRY_EXPRESSION_NODE_H

#include <string>
#include "ast-callable-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"

class ASTCurryExpressionNode : public ASTCallableExpressionNode {
private:
    ASTCallableExpressionNode* _callableExpression;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTCurryExpressionNode(ASTCallableExpressionNode* callableExpression, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTCallableExpressionNode* getCallableExpression();
    unsigned long numArguments();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_CURRY_EXPRESSION_NODE_H

//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "ast-array-access-expression-node.h"

class ASTArrayAccessInvocationExpressionNode : public ASTExpressionNode {
private:
    ASTArrayAccessExpressionNode* _arrayAccess;
    ASTFunctionArgumentListNode* _arguments;
public:
    ASTArrayAccessInvocationExpressionNode(ASTArrayAccessExpressionNode* arrayAccess, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTArrayAccessExpressionNode* getArrayAccess();
    ASTExpressionNode* getSource();
    ASTArrayAccessNode* getIndex();
    unsigned long numArguments();
    bool isArrayPrototypeInvocation();
    bool isRefPrototypeInvocation();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

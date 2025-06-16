//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-callable-expression-node.h"
#include "../ast-class-nodes/ast-class-method-call-node.h"
#include "../ast-class-nodes/ast-class-access-node.h"
#include "ast-object-access-expression-node.h"

class ASTObjectAccessInvocationExpressionNode : public ASTCallableExpressionNode {
private:
    ASTObjectAccessExpressionNode* _objectAccess;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTObjectAccessInvocationExpressionNode(ASTObjectAccessExpressionNode* objectAccess, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTObjectAccessExpressionNode* getObjectAccess();
    ASTObjectAccessSourceNode* getSource();
    ASTObjectAccessTargetNode* getTarget();
    unsigned long numArguments();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H

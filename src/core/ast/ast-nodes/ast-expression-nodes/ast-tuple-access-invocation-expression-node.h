//
// Created by Johny Georges on 2025-06-18.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-callable-expression-node.h"
#include "ast-tuple-access-expression.h"

class ASTTupleAccessInvocationExpressionNode : public ASTCallableExpressionNode {
private:
    ASTTupleAccessExpressionNode* _tupleAccess;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTTupleAccessInvocationExpressionNode(ASTTupleAccessExpressionNode* tupleAccess, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTTupleAccessExpressionNode* getObjectAccess();
    ASTObjectAccessSourceNode* getSource();
    ASTTupleAccessNode* getIndex();
    unsigned long numArguments();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE_H

//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-callable-expression-node.h"
#include "../ast-class-nodes/ast-class-method-call-node.h"
#include "../ast-class-nodes/ast-class-access-node.h"

class ASTClassMethodInvocationExpressionNode : public ASTCallableExpressionNode {
private:
    std::shared_ptr<ASTClassAccessNode> _classAccess;
    std::shared_ptr<ASTClassMethodCallNode> _method;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
public:
    explicit ASTClassMethodInvocationExpressionNode(std::shared_ptr<ASTClassAccessNode> classAccess, std::shared_ptr<ASTClassMethodCallNode> name, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::shared_ptr<ASTClassMethodCallNode> getName();
    std::shared_ptr<ASTClassAccessNode> getClassAccess();
    uint64_t numArguments();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

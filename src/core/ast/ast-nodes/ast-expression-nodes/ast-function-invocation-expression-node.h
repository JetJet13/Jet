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
    std::shared_ptr<ASTExpressionNode> _function;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
    std::shared_ptr<FunctionInvocationTypeSignature> _typeSignature = std::make_shared<FunctionInvocationTypeSignature>();
public:
    explicit ASTFunctionInvocationExpressionNode(std::shared_ptr<ASTExpressionNode> function, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::shared_ptr<ASTExpressionNode> getFunction();
    uint64_t numArguments();
    void setTypeSignature(std::shared_ptr<FunctionInvocationTypeSignature> functionInvocationTypeSignature);
    std::shared_ptr<FunctionInvocationTypeSignature> getInvocationTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_INVOCATION_EXPRESSION_NODE_H

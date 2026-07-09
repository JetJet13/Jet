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
    std::shared_ptr<ASTCallableExpressionNode> _callableExpression;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
public:
    explicit ASTCurryExpressionNode(std::shared_ptr<ASTCallableExpressionNode> callableExpression, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::shared_ptr<ASTCallableExpressionNode> getCallableExpression();
    unsigned long numArguments();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_CURRY_EXPRESSION_NODE_H

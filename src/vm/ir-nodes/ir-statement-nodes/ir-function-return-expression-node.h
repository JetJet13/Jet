//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_FUNCTION_RETURN_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_RETURN_EXPRESSION_NODE_H


#include "../ir-expression-nodes/ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "ir-statement-node.h"


class IRFunctionReturnExpressionNode : public IRStatementNode {
private:
    std::shared_ptr<ASTFunctionReturnExpressionNode> _node;
    std::optional<std::shared_ptr<IRExpressionNode>> _irExpression;
public:
    IRFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnExpressionNode> node, std::optional<std::shared_ptr<IRExpressionNode>> irExpression = {});
    std::optional<std::shared_ptr<IRExpressionNode>> getReturnExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_RETURN_EXPRESSION_NODE_H

//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-return-expression-node.h"

IRFunctionReturnExpressionNode::IRFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnExpressionNode> node, std::optional<std::shared_ptr<IRExpressionNode>> irExpression) {
    _node = node;
    _irExpression = irExpression;
}

std::optional<std::shared_ptr<IRExpressionNode>> IRFunctionReturnExpressionNode::getReturnExpression() {
    return _irExpression;
}

IRNodeType IRFunctionReturnExpressionNode::getNodeType() {
    return IR_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string IRFunctionReturnExpressionNode::toString() {
    return "IR_FUNCTION_RETURN_EXPRESSION_NODE";
}

void IRFunctionReturnExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    if (_irExpression) {
        _irExpression.value()->print(stream);
    }
}
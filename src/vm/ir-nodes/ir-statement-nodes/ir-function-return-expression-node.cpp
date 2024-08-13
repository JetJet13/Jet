//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-return-expression-node.h"
#include "../../ir-injector/ir-injector-map.h"

IRFunctionReturnExpressionNode::IRFunctionReturnExpressionNode(ASTFunctionReturnExpressionNode* node, IRExpressionNode* irExpression) {
    _node = node;
    _irExpression = irExpression;
}

void IRFunctionReturnExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder,
                                                         IRInjectorMap *injectorMap) {
    auto irExpressionValue = _irExpression->insertSelfIntoBlock(builder, injectorMap);
    builder->get()->CreateRet(irExpressionValue);
}

IRNodeType IRFunctionReturnExpressionNode::getNodeType() {
    return IR_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string IRFunctionReturnExpressionNode::toString() {
    return "IR_FUNCTION_RETURN_EXPRESSION_NODE";
}

void IRFunctionReturnExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}
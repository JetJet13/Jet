//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"
#include "../../ir-injector/ir-injector-map.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(ASTLiteralExpressionNode* node, IRLiteralNode* irValue, IRType* irType) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
}

llvm::Value * IRLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder,
                                                           IRInjectorMap *injectorMap) {
    return _irValue->getConstantIRValue();
}

IRType* IRLiteralExpressionNode::getIRType() {
    return _irType;
}

llvm::Constant* IRLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRNodeType IRLiteralExpressionNode::getNodeType() {
    return IR_LITERAL_EXPRESSION_NODE;
}

std::string IRLiteralExpressionNode::toString() {
    return "IR_LITERAL_EXPRESSION_NODE";
}

void IRLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}
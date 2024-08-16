//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irExpression, IRType* type, IRInstructionNode* sourceAllocation) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

//llvm::Value * IRUnaryArithmeticExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder,
//                                                                   IRInjectorMap *injectorMap) {
//    return builder->get()->Insert(_irValue);
//}

llvm::BinaryOperator* IRUnaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRUnaryArithmeticExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRType* IRUnaryArithmeticExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRUnaryArithmeticExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRUnaryArithmeticExpressionNode::getNodeType() {
    return IR_UNARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRUnaryArithmeticExpressionNode::toString() {
    return "IR_UNARY_EXPRESSION_NODE";
}

void IRUnaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}
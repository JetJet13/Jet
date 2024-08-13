//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-logical-expression-node.h"

IRLogicalExpressionNode::IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRType* type, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRInstructionNode* sourceAllocation) {
    _astNode = astNode;
    _irValue = irValue;
    _type = type;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _sourceAllocation = sourceAllocation;
}

llvm::Value * IRLogicalExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder,
                                                           IRInjectorMap *injectorMap) {
    auto allocation = builder->get()->Insert(_sourceAllocation->getValue());
    auto irLeftNodeValue = _irLeftNode->insertSelfIntoBlock(builder, injectorMap);
    auto leftNodeValue = builder->get()->CreateLoad(_irLeftNode->getIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = _irRightNode->insertSelfIntoBlock(builder, injectorMap);
    auto rightNodeValue = builder->get()->CreateLoad(_irRightNode->getIRType()->getType(), irRightNodeValue);

    auto result = builder->get()->CreateBinOp(_irValue->getOpcode(), leftNodeValue, rightNodeValue);
    builder->get()->CreateStore(result, allocation);
    return allocation;
}

IRType* IRLogicalExpressionNode::getIRType() {
    return _type;
}

llvm::BinaryOperator* IRLogicalExpressionNode::getValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRLogicalExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRNodeType IRLogicalExpressionNode::getNodeType() {
    return IR_LOGICAL_EXPRESSION_NODE;
}

std::string IRLogicalExpressionNode::toString() {
    return "IR_LOGICAL_EXPRESSION_NODE";
}

void IRLogicalExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}
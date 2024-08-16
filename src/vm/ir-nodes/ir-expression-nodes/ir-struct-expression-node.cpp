//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(ASTStructExpressionNode* astNode, IRInstructionNode* irValue, IRType* type, std::vector<IRExpressionNode*> irValues) {
    _node = astNode;
    _irValue = irValue;
    _irValues = irValues;
    _type = type;
}

//llvm::Value * IRStructExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {
//    return injectorMap->getStructInjector()->inject(this, builder);
//}

IRType* IRStructExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRStructExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

unsigned long IRStructExpressionNode::size() {
    return _irValues.size();
}

llvm::Value* IRStructExpressionNode::getValue() {
    return _irValue->getValue();
}

std::vector<IRExpressionNode*>* IRStructExpressionNode::getValues() {
    return &_irValues;
}

std::optional<IRInstructionNode*> IRStructExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRStructExpressionNode::getSourceAllocationAtIndex(unsigned long index) {
    return _irValues[index]->getSourceAllocation();
}

std::optional<IRInstructionNode*> IRStructExpressionNode::getRootAllocationAtIndex(unsigned long index) {
    return _irValues[index]->getRootAllocation();
}


IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}

void IRStructExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}
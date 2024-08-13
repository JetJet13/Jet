//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-comparison-expression-node.h"

IRBinaryComparisonExpressionNode::IRBinaryComparisonExpressionNode(ASTBinaryExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type, IRInstructionNode* sourceAllocation) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

llvm::Value * IRBinaryComparisonExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder,
                                                                    IRInjectorMap *injectorMap) {
    auto allocation = builder->get()->Insert(_sourceAllocation->getValue());
    auto irLeftNodeValue = _irLeftNode->insertSelfIntoBlock(builder, injectorMap);
    auto leftNodeValue = builder->get()->CreateLoad(_irLeftNode->getIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = _irRightNode->insertSelfIntoBlock(builder, injectorMap);
    auto rightNodeValue = builder->get()->CreateLoad(_irRightNode->getIRType()->getType(), irRightNodeValue);

    auto result = builder->get()->CreateCmp(_irValue->getPredicate(), leftNodeValue, rightNodeValue);
    builder->get()->CreateStore(result, allocation);
    return allocation;
}

llvm::CmpInst* IRBinaryComparisonExpressionNode::getValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRBinaryComparisonExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRType* IRBinaryComparisonExpressionNode::getIRType() {
    return _type;
}

IRNodeType IRBinaryComparisonExpressionNode::getNodeType() {
    return IR_BINARY_COMPARISON_EXPRESSION_NODE;
}

std::string IRBinaryComparisonExpressionNode::toString() {
    return "IR_BINARY_COMPARISON_EXPRESSION_NODE";
}

void IRBinaryComparisonExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}
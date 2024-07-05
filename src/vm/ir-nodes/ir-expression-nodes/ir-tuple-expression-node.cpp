//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(ASTTupleExpressionNode* astNode, llvm::AllocaInst* irAllocation, std::vector<IRExpressionNode*> irValues, llvm::GetElementPtrInst* irPointer) {
    _astNode = astNode;
    _irAllocation = irAllocation;
    _irValues = irValues;
    _irPointer = irPointer;
    _irStatements = std::vector<llvm::Value*>();
    this->generateStatements();
}

llvm::AllocaInst* IRTupleExpressionNode::getIRValue() {
    return _irAllocation;
}

IRNodeType IRTupleExpressionNode::getNodeType() {
    return IR_TUPLE_EXPRESSION_NODE;
}

std::string IRTupleExpressionNode::toString() {
    return "IR_TUPLE_EXPRESSION_NODE";
}

void IRTupleExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto irStatement : _irStatements) {
        irStatement->print(**stream);
        stream->get()->write('\n');
    }
}

void IRTupleExpressionNode::generateStatements() {
    _irStatements.push_back(_irAllocation);
    _irStatements.push_back(_irPointer);
    auto numElements = _irValues.size();
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        _irStatements.push_back(irExpression->getIRValue());
        _irStatements.push_back(
                new llvm::StoreInst(irExpression->getIRValue(), _irPointer, false, _irAllocation->getAlign())
        );
    }
}
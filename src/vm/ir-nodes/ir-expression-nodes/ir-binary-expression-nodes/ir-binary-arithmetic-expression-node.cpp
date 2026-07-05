//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-arithmetic-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

IRBinaryArithmeticExpressionNode::IRBinaryArithmeticExpressionNode(std::shared_ptr<ASTBinaryArithmeticExpressionNode> astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, std::shared_ptr<IRType> type) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
}

std::vector<IRExpressionNode*> IRBinaryArithmeticExpressionNode::getListOfOperands() {
    auto expressionList = std::vector<IRExpressionNode*>();
    if (_irLeftNode->isGrouped()) {
        Logger::log("LEFT NODE IS GROUPED");
    }
    if (_irLeftNode->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE) && !_irLeftNode->isGrouped()) {
        auto leftNode = (IRBinaryArithmeticExpressionNode*)_irLeftNode;
        auto leftNodeListOfExpressions = leftNode->getListOfOperands();
        expressionList.insert(
                expressionList.end(),
                leftNodeListOfExpressions.begin(),
                leftNodeListOfExpressions.end()
        );
    } else {
        expressionList.push_back(_irLeftNode);
    }

    if (_irRightNode->isGrouped()) {
        Logger::log("RIGHT NODE IS GROUPED");
    }
    if (_irRightNode->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE) && !_irRightNode->isGrouped()) {
        auto rightNode = (IRBinaryArithmeticExpressionNode*)_irRightNode;
        auto rightNodeListOfExpressions = rightNode->getListOfOperands();
        expressionList.insert(
                expressionList.end(),
                rightNodeListOfExpressions.begin(),
                rightNodeListOfExpressions.end()
        );
    } else {
        expressionList.push_back(_irRightNode);
    }
    return expressionList;
}

std::vector<IRBinaryOperatorNode*> IRBinaryArithmeticExpressionNode::getListOfOperations() {
    auto operationList = std::vector<IRBinaryOperatorNode*>();

    if (_irLeftNode->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE) && !_irLeftNode->isGrouped()) {
        auto leftNode = (IRBinaryArithmeticExpressionNode*)_irLeftNode;
        auto leftNodeListOfExpressions = leftNode->getListOfOperations();
        operationList.insert(
                operationList.end(),
                leftNodeListOfExpressions.begin(),
                leftNodeListOfExpressions.end()
        );
    }

    operationList.push_back(new IRBinaryOperatorNode(_irValue));
    if (_irRightNode->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE) && !_irRightNode->isGrouped()) {
        auto rightNode = (IRBinaryArithmeticExpressionNode*)_irRightNode;
        auto rightNodeListOfExpressions = rightNode->getListOfOperations();
        operationList.insert(
            operationList.end(),
            rightNodeListOfExpressions.begin(),
            rightNodeListOfExpressions.end()
        );
    }
    return operationList;
}

void IRBinaryArithmeticExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

llvm::BinaryOperator* IRBinaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

IRExpressionNode* IRBinaryArithmeticExpressionNode::getLeftNode() {
    return _irLeftNode;
}

IRExpressionNode* IRBinaryArithmeticExpressionNode::getRightNode() {
    return _irRightNode;
}

std::shared_ptr<IRType> IRBinaryArithmeticExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRBinaryArithmeticExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRBinaryArithmeticExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRBinaryArithmeticExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRBinaryArithmeticExpressionNode::getNodeType() {
    return IR_BINARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRBinaryArithmeticExpressionNode::toString() {
    return "IR_BINARY_ARITHMETIC_EXPRESSION_NODE";
}

void IRBinaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}
//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-array-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTArrayExpressionNode::ASTArrayExpressionNode(std::shared_ptr<ASTArrayNode> array) {
    _array = array;
    _children.push_back(_array);
}

std::shared_ptr<ASTArrayNode> ASTArrayExpressionNode::getArray() {
    return _array;
}

std::vector<std::shared_ptr<ASTExpressionNode>>* ASTArrayExpressionNode::getElements() {
    return _array->getElements();
}

std::shared_ptr<ASTArrayExpressionNode> ASTArrayExpressionNode::addElement(std::shared_ptr<ASTExpressionNode> element) {
    _array->getElements()->push_back(element);
    return std::dynamic_pointer_cast<ASTArrayExpressionNode>(shared_from_this());
}

ArrayTypeSignature* ASTArrayExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTArrayExpressionNode::setTypeSignature(ArrayTypeSignature* arrayTypeSignature) {
    _typeSignature = arrayTypeSignature;
}

unsigned long ASTArrayExpressionNode::size() {
    return _array->getElements()->size();
}

Position* ASTArrayExpressionNode::getStartPosition() {
    return _array->getStartPosition();
}

Position* ASTArrayExpressionNode::getEndPosition() {
    return _array->getEndPosition();
}

ASTNodeType ASTArrayExpressionNode::getNodeType() {
    return AST_ARRAY_EXPRESSION_NODE;
}

std::string ASTArrayExpressionNode::toString() {
    return "ARRAY_EXPRESSION";
}

bool ASTArrayExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayExpressionNode>(other);
    if (this->size() != otherNode->size()) {
        return false;
    }
    return this->getArray()->isSameAs(otherNode->getArray());
}

void ASTArrayExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _array->print();
    Logger::log("----------");
}

std::string ASTArrayExpressionNode::toSourceCode() {
    return _array->toSourceCode();
}
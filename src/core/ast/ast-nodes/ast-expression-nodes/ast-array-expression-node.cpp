//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-array-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTArrayExpressionNode::ASTArrayExpressionNode(ASTArrayNode* array) {
    _array = array;
    _children.push_back(_array);
}

ASTArrayNode* ASTArrayExpressionNode::getArray() {
    return _array;
}

std::vector<ASTExpressionNode*>* ASTArrayExpressionNode::getElements() {
    return _array->getElements();
}

ASTArrayExpressionNode* ASTArrayExpressionNode::addElement(ASTExpressionNode* element) {
    _array->getElements()->push_back(element);
    return this;
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

void ASTArrayExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _array->markElementsAsReferenced();
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

bool ASTArrayExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayExpressionNode*)other;
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
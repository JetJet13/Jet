//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-array-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayExpressionNode::ASTArrayExpressionNode() {
    _elements = new std::vector<ASTExpressionNode*>();
}

ASTArrayExpressionNode::ASTArrayExpressionNode(std::vector<ASTExpressionNode*> elements) {
    _elements = new std::vector<ASTExpressionNode*>();
    for (auto element: elements) {
        _elements->push_back(element);
    }
}

std::vector<ASTExpressionNode*>* ASTArrayExpressionNode::getElements() {
    return _elements;
}

ASTArrayExpressionNode* ASTArrayExpressionNode::addElement(ASTExpressionNode* element) {
    _elements->push_back(element);
    return this;
}

unsigned long ASTArrayExpressionNode::size() {
    return _elements->size();
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
    auto otherNodeElements = otherNode->getElements();
    if (this->size() != otherNode->size()) {
        return false;
    }
    for (int i = 0; i < this->size(); i++) {
        if (!_elements->at(i)->isSameAs(otherNodeElements->at(i))) {
            return false;
        }
    }

    return true;
}

void ASTArrayExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto element : *_elements) {
        element->print();
    }
    Logger::log("----------");
}
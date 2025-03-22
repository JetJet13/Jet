//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-node.h"
#include "../ast-expression-nodes/ast-array-expression-node.h"
#include "ast-array-access-node.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayNode::ASTArrayNode(ASTLeftBracketNode* leftBracket, ASTRightBracketNode* rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _elements = new std::vector<ASTExpressionNode*>();
}

ASTArrayNode::ASTArrayNode(ASTLeftBracketNode* leftBracket, std::vector<ASTExpressionNode*> elements, ASTRightBracketNode* rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _elements = new std::vector<ASTExpressionNode*>();
    for (auto element: elements) {
        this->addElement(element);
    }
}

ASTArrayNode* ASTArrayNode::addElement(ASTExpressionNode* element) {
    _elements->push_back(element);
    _children.push_back(element);
    return this;
}

void ASTArrayNode::markElementsAsReferenced() {
    for (int i = 0; i < _elements->size(); ++i) {
        _elements->at(i)->markAsReferenced();
    }
}

ASTLeftBracketNode* ASTArrayNode::getLeftBracket() {
    return _leftBracket;
}

ASTRightBracketNode* ASTArrayNode::getRightBracket() {
    return _rightBracket;
}

std::optional<ASTExpressionNode*> ASTArrayNode::getFirstElement() {
    if (_elements->at(0)) {
        return _elements->at(0);
    }
    return {};
}

std::vector<ASTExpressionNode*>* ASTArrayNode::getElements() {
    return _elements;
}

Position* ASTArrayNode::getStartPosition() {
    return _leftBracket->getStartPosition();
}

Position* ASTArrayNode::getEndPosition() {
    return _rightBracket->getEndPosition();
}

ASTNodeType ASTArrayNode::getNodeType() {
    return AST_ARRAY_NODE;
}

std::string ASTArrayNode::toString() {
    return "ARRAY";
}

void ASTArrayNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto element : *_elements) {
        element->toString();
    }
    Logger::log("----------");
}

std::string ASTArrayNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftBracket);

    for (auto element : *_elements) {
        sourceCodeBuilder.addWithWhitespace(element);
    }

    sourceCodeBuilder.addWithWhitespace(_rightBracket);
    return sourceCodeBuilder.build();
}
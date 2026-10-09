// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-node.h"
#include "../ast-expression-nodes/ast-array-expression-node.h"
#include "ast-array-access-node.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayNode::ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::shared_ptr<ASTRightBracketNode> rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _elements = std::vector<std::shared_ptr<ASTExpressionNode>>();
}

ASTArrayNode::ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::vector<std::shared_ptr<ASTExpressionNode>> elements, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTRightBracketNode> rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _commas = commas;
    _elements = std::vector<std::shared_ptr<ASTExpressionNode>>();
    for (auto element: elements) {
        _elements.push_back(element);
        _children.push_back(element);
    }
}

std::shared_ptr<ASTArrayNode> ASTArrayNode::addElement(std::shared_ptr<ASTExpressionNode> element) {
    _elements.push_back(element);
    _children.push_back(element);
    return std::dynamic_pointer_cast<ASTArrayNode>(shared_from_this());
}

std::shared_ptr<ASTArrayNode> ASTArrayNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTArrayNode>(shared_from_this());
}

std::shared_ptr<ASTLeftBracketNode> ASTArrayNode::getLeftBracket() {
    return _leftBracket;
}

std::shared_ptr<ASTRightBracketNode> ASTArrayNode::getRightBracket() {
    return _rightBracket;
}

std::optional<std::shared_ptr<ASTExpressionNode>> ASTArrayNode::getFirstElement() {
    if (_elements.at(0)) {
        return _elements.at(0);
    }
    return {};
}

std::vector<std::shared_ptr<ASTExpressionNode>>* ASTArrayNode::getElements() {
    return &_elements;
}

std::shared_ptr<Position> ASTArrayNode::getStartPosition() {
    return _leftBracket->getStartPosition();
}

std::shared_ptr<Position> ASTArrayNode::getEndPosition() {
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
    for (auto element : _elements) {
        element->toString();
    }
    Logger::log("----------");
}

std::string ASTArrayNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftBracket);
    for (uint64_t i = 0; i < _elements.size(); ++i) {
        sourceCodeBuilder.add(_elements.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }

    sourceCodeBuilder.add(_rightBracket);
    return sourceCodeBuilder.build();
}
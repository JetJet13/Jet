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

std::shared_ptr<TypeSignature> ASTArrayExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<ArrayTypeSignature> ASTArrayExpressionNode::getArrayTypeSignature() {
    return std::dynamic_pointer_cast<ArrayTypeSignature>(_typeSignature);
}

void ASTArrayExpressionNode::setTypeSignature(std::shared_ptr<ArrayTypeSignature> arrayTypeSignature) {
    _typeSignature = arrayTypeSignature;
}

uint64_t ASTArrayExpressionNode::size() {
    return _array->getElements()->size();
}

std::shared_ptr<Position> ASTArrayExpressionNode::getStartPosition() {
    return _array->getStartPosition();
}

std::shared_ptr<Position> ASTArrayExpressionNode::getEndPosition() {
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
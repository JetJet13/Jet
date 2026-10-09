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
// Created by Johny Georges on 2024-03-12.
//

#include "ast-array-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessNode::ASTArrayAccessNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::shared_ptr<ASTExpressionNode> index, std::shared_ptr<ASTRightBracketNode> rightBracket) {
    _leftBracket = leftBracket;
    _rightBracket = rightBracket;
    _index = index;
    _children.push_back(_leftBracket);
    _children.push_back(_rightBracket);
    _children.push_back(_index);
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessNode::getIndex() {
    return _index;
}

std::shared_ptr<Position> ASTArrayAccessNode::getStartPosition() {
    return _leftBracket->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessNode::getEndPosition() {
    return _rightBracket->getEndPosition();
}

ASTNodeType ASTArrayAccessNode::getNodeType() {
    return AST_ARRAY_ACCESS_NODE;
}

std::string ASTArrayAccessNode::toString() {
    return "ARRAY_ACCESS";
}

bool ASTArrayAccessNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessNode>(other);
    return _index->isSameAs(otherNode->getIndex());

}

void ASTArrayAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _index->print();
    Logger::log("----------");
}

std::string ASTArrayAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftBracket)
    ->add(_index)
    ->add(_rightBracket);
    return sourceCodeBuilder.build();
}
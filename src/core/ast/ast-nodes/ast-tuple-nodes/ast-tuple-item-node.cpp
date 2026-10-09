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
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleItemNode::ASTTupleItemNode(std::shared_ptr<ASTExpressionNode> item) {
    _item = item;
    _children.push_back(_item);
}

std::shared_ptr<ASTNode> ASTTupleItemNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return this->getItem();
    }
    return shared_from_this();
}

std::shared_ptr<ASTExpressionNode> ASTTupleItemNode::getItem() {
    return _item;
}

std::shared_ptr<Position> ASTTupleItemNode::getStartPosition() {
    return _item->getStartPosition();
}

std::shared_ptr<Position> ASTTupleItemNode::getEndPosition() {
    return _item->getEndPosition();
}

ASTNodeType ASTTupleItemNode::getNodeType() {
    return AST_TUPLE_ITEM_NODE;
}

std::string ASTTupleItemNode::toString() {
    return "TUPLE_ITEM";
}

bool ASTTupleItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleItemNode>(other);
    return this->getItem()->isSameAs(otherNode->getItem());
}

void ASTTupleItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}

std::string ASTTupleItemNode::toSourceCode() {
    return _item->toSourceCode();
}
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
// Created by Johny Georges on 2024-03-28.
//

#include "ast-if-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTIfStatementNode::ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock) {
    _ifBlock = ifBlock;
    _elseIfBlocks = std::vector<std::shared_ptr<ASTElseIfBlockNode>>();
    _elseBlock = {};
    _children.push_back(_ifBlock);
}

ASTIfStatementNode::ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock, std::vector<std::shared_ptr<ASTElseIfBlockNode>> elseIfBlocks, std::optional<std::shared_ptr<ASTElseBlockNode>> elseBlock) {
    _ifBlock = ifBlock;
    _children.push_back(_ifBlock);

    _elseBlock = elseBlock;
    if (_elseBlock) {
        _children.push_back(_elseBlock.value());
    }

    _elseIfBlocks = std::vector<std::shared_ptr<ASTElseIfBlockNode>>();
    for (auto elseIfBlock: elseIfBlocks) {
        _elseIfBlocks.push_back(elseIfBlock);
        _children.push_back(elseIfBlock);
    }
}

std::shared_ptr<ASTIfStatementNode> ASTIfStatementNode::addElseIfBlock(std::shared_ptr<ASTElseIfBlockNode> elseIfBlock) {
    _elseIfBlocks.push_back(elseIfBlock);
    return std::dynamic_pointer_cast<ASTIfStatementNode>(shared_from_this());
}

std::shared_ptr<ASTIfBlockNode> ASTIfStatementNode::getIfBlock() {
    return _ifBlock;
}

std::vector<std::shared_ptr<ASTElseIfBlockNode>>* ASTIfStatementNode::getElseIfBlocks() {
    return &_elseIfBlocks;
}

std::optional<std::shared_ptr<ASTElseBlockNode>> ASTIfStatementNode::getElseBlock() {
    return _elseBlock;
}

bool ASTIfStatementNode::onlyHasIfBlock() {
    return _elseIfBlocks.empty() && !_elseBlock;
}

std::shared_ptr<Position> ASTIfStatementNode::getStartPosition() {
    return _ifBlock->getStartPosition();
}

std::shared_ptr<Position> ASTIfStatementNode::getEndPosition() {
    if (_elseBlock) {
        return _elseBlock.value()->getEndPosition();
    }

    if (_elseIfBlocks.empty()) {
        return _ifBlock->getEndPosition();
    }

    return _elseIfBlocks[_elseIfBlocks.size() - 1]->getEndPosition();
}

ASTNodeType ASTIfStatementNode::getNodeType() {
    return AST_IF_STATEMENT_NODE;
}

std::string ASTIfStatementNode::toString() {
    return "IF_STATEMENT";
}

bool ASTIfStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTIfStatementNode>(other);
    if (!this->getIfBlock()->isSameAs(otherNode->getIfBlock())) {
        return false;
    }

    if (!_elseBlock.has_value() && otherNode->getElseBlock().has_value() ||
        _elseBlock.has_value() && !otherNode->getElseBlock().has_value()) {
        return false;
    }

    if (_elseBlock.has_value() && otherNode->getElseBlock().has_value() &&
        !_elseBlock.value()->isSameAs(otherNode->getElseBlock().value())) {
        return false;
    }

    for (uint64_t i = 0; i < _elseIfBlocks.size(); ++i) {
        if (!_elseIfBlocks[i]->isSameAs(otherNode->getElseIfBlocks()->at(i))) {
            return false;
        }
    }
    return true;
}


void ASTIfStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _ifBlock->print();
    for (auto elseIfBlock : _elseIfBlocks) {
        elseIfBlock->print();
    }
    if (_elseBlock) {
        _elseBlock.value()->print();
    }
    Logger::log("----------");
}

std::string ASTIfStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_ifBlock);
    for (auto elseIfBlock : _elseIfBlocks) {
        sourceCodeBuilder.add(elseIfBlock);
    }

    if (_elseBlock) {
        sourceCodeBuilder.add(_elseBlock.value());
    }

    return sourceCodeBuilder.build();
}
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
// Created by Johny Georges on 2024-04-01.
//

#include "ast-finally-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTFinallyBlockNode::ASTFinallyBlockNode(std::shared_ptr<ASTFinallyNode> finallyKeyword, std::shared_ptr<ASTControlFlowBlockNode> block) {
    _finallyKeyword = finallyKeyword;
    _block = block;
    _children.push_back(_finallyKeyword);
    _children.push_back(_block);
}

std::shared_ptr<ASTControlFlowBlockNode> ASTFinallyBlockNode::getBlock() {
    return _block;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTFinallyBlockNode::getReturnStatements() {
    return _block->getReturnStatements();
}

std::shared_ptr<Position> ASTFinallyBlockNode::getStartPosition() {
    return _finallyKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTFinallyBlockNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTFinallyBlockNode::getNodeType() {
    return AST_FINALLY_BLOCK_NODE;
}

std::string ASTFinallyBlockNode::toString() {
    return "FINALLY_BLOCK";
}

bool ASTFinallyBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFinallyBlockNode>(other);

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTFinallyBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _block->print();
    Logger::log("----------");
}

std::string ASTFinallyBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_finallyKeyword)
    ->add(_block);
    return sourceCodeBuilder.build();
}
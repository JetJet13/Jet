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
// Created by Johny Georges on 2024-03-29.
//

#include "ast-while-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTWhileStatementNode::ASTWhileStatementNode(std::shared_ptr<ASTWhileNode> whileKeyword, std::shared_ptr<ASTControlFlowConditionNode> condition, std::shared_ptr<ASTControlFlowBlockNode> block) {
    _whileKeyword = whileKeyword;
    _condition = condition;
    _block = block;
    _children.push_back(_whileKeyword);
    _children.push_back(_condition);
    _children.push_back(_block);
}

std::shared_ptr<ASTControlFlowBlockNode> ASTWhileStatementNode::getBlock() {
    return _block;
}

std::shared_ptr<ASTControlFlowConditionNode> ASTWhileStatementNode::getCondition() {
    return _condition;
}

std::shared_ptr<Position> ASTWhileStatementNode::getStartPosition() {
    return _whileKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTWhileStatementNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTWhileStatementNode::getNodeType() {
    return AST_WHILE_STATEMENT_NODE;
}

std::string ASTWhileStatementNode::toString() {
    return "WHILE_STATEMENT";
}

bool ASTWhileStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTWhileStatementNode>(other);

    return  this->getCondition()->isSameAs(otherNode->getCondition()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTWhileStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTWhileStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_whileKeyword)
    ->add(_condition)
    ->add(_block);
    return sourceCodeBuilder.build();
}
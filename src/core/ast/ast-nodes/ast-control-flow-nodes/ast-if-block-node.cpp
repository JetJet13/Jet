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

#include "ast-if-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTIfBlockNode::ASTIfBlockNode(std::shared_ptr<ASTIfNode> ifKeyword, std::shared_ptr<ASTControlFlowConditionNode> condition, std::shared_ptr<ASTControlFlowBlockNode> block) {
    _ifKeyword = ifKeyword;
    _condition = condition;
    _block = block;
    _children.push_back(_condition);
    _children.push_back(_block);
}

std::shared_ptr<ASTControlFlowBlockNode> ASTIfBlockNode::getBlock() {
    return _block;
}

std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* ASTIfBlockNode::getReturnStatements() {
    return _block->getReturnStatements();
}

std::shared_ptr<ASTControlFlowConditionNode> ASTIfBlockNode::getCondition() {
    return _condition;
}

std::shared_ptr<Position> ASTIfBlockNode::getStartPosition() {
    return _ifKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTIfBlockNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTIfBlockNode::getNodeType() {
    return AST_IF_BLOCK_NODE;
}

std::string ASTIfBlockNode::toString() {
    return "IF_BLOCK";
}

bool ASTIfBlockNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTIfBlockNode>(other);

    return  this->getCondition()->isSameAs(otherNode->getCondition()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTIfBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTIfBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_ifKeyword)
    ->add(_condition)
    ->add(_block);
    return sourceCodeBuilder.build();
}
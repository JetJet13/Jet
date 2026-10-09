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

#include "ast-for-in-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTForInStatementNode::ASTForInStatementNode(std::shared_ptr<ASTForNode> forKeyword, std::shared_ptr<ASTForInVariableNode> variable, std::shared_ptr<ASTForInNode> inKeyword, std::shared_ptr<ASTForInSourceNode> source, std::shared_ptr<ASTControlFlowBlockNode> block) {
    _forKeyword = forKeyword;
    _variable = variable;
    _inKeyword = inKeyword;
    _source = source;
    _block = block;
    _children.push_back(_forKeyword);
    _children.push_back(_variable);
    _children.push_back(_inKeyword);
    _children.push_back(_source);
    _children.push_back(_block);
}

std::shared_ptr<ASTForInVariableNode> ASTForInStatementNode::getVariable() {
    return _variable;
}

std::shared_ptr<ASTForInSourceNode> ASTForInStatementNode::getSource() {
    return _source;
}

std::shared_ptr<ASTControlFlowBlockNode> ASTForInStatementNode::getBlock() {
    return _block;
}

std::shared_ptr<Position> ASTForInStatementNode::getStartPosition() {
    return _forKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTForInStatementNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTForInStatementNode::getNodeType() {
    return AST_FOR_IN_STATEMENT_NODE;
}

std::string ASTForInStatementNode::toString() {
    return "FOR_IN_STATEMENT";
}

bool ASTForInStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTForInStatementNode>(other);

    return  this->getVariable()->isSameAs(otherNode->getVariable()) &&
            this->getSource()->isSameAs(otherNode->getSource()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTForInStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    _source->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTForInStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_forKeyword)
    ->add(_variable)
    ->add(_inKeyword)
    ->add(_source)
    ->add(_block);
    return sourceCodeBuilder.build();
}
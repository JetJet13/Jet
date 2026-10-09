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
// Created by Johny Georges on 2024-03-14.
//

#include "ast-object-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessExpressionNode::ASTObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTPeriodNode> period, std::shared_ptr<ASTObjectAccessTargetNode> property) {
    _source = source;
    _period = period;
    _target = property;
    _children.push_back(_source);
    _children.push_back(_target);
}

std::shared_ptr<ASTObjectAccessSourceNode> ASTObjectAccessExpressionNode::getSource() {
    return _source;
}

std::shared_ptr<ASTObjectAccessTargetNode> ASTObjectAccessExpressionNode::getTarget() {
    return _target;
}

std::shared_ptr<Position> ASTObjectAccessExpressionNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessExpressionNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTObjectAccessExpressionNode::getNodeType() {
    return AST_OBJECT_ACCESS_EXPRESSION_NODE;
}

std::string ASTObjectAccessExpressionNode::toString() {
    return "OBJECT_ACCESS_EXPRESSION";
}

bool ASTObjectAccessExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource()) &&
            this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTObjectAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _target->print();
    Logger::log("----------");
}

std::string ASTObjectAccessExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
    ->add(_period)
    ->add(_target);
    return sourceCodeBuilder.build();
}
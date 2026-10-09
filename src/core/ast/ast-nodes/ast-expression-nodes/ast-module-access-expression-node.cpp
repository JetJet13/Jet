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
// Created by Johny Georges on 2024-11-05.
//

#include "ast-module-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessExpressionNode::ASTModuleAccessExpressionNode(std::shared_ptr<ASTModuleAccessSourceNode> source, std::shared_ptr<ASTModuleAccessNode> moduleAccess, std::shared_ptr<ASTModuleAccessTargetNode> target) {
    _source = source;
    _moduleAccess = moduleAccess;
    _target = target;
    _children.push_back(_source);
    _children.push_back(_moduleAccess);
    _children.push_back(_target);
}

std::shared_ptr<ASTModuleAccessSourceNode> ASTModuleAccessExpressionNode::getSource() {
    return _source;
}

std::shared_ptr<ASTModuleAccessTargetNode> ASTModuleAccessExpressionNode::getTarget() {
    return _target;
}

std::string ASTModuleAccessExpressionNode::getModuleTargetName() {
    return _target->getTarget()->getIdentifierNode()->getId();
}

std::string ASTModuleAccessExpressionNode::getModuleName() {
    return _source->getSource()->getIdentifierNode()->getId();
}

std::string ASTModuleAccessExpressionNode::getModuleId() {
    return _source->getSource()->getIdentifierNode()->getId();
}

std::shared_ptr<Position> ASTModuleAccessExpressionNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessExpressionNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTModuleAccessExpressionNode::getNodeType() {
    return AST_MODULE_ACCESS_EXPRESSION_NODE;
}

std::string ASTModuleAccessExpressionNode::toString() {
    return "MODULE_ACCESS_EXPRESSION";
}

bool ASTModuleAccessExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTModuleAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _target->print();
    Logger::log("----------");
}

std::string ASTModuleAccessExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
            ->add(_moduleAccess)
            ->add(_target);
    return sourceCodeBuilder.build();
}
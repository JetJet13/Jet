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
// Created by Johny Georges on 2024-04-10.
//

#include "ast-variable-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableDefinitionNode::ASTVariableDefinitionNode(std::shared_ptr<ASTVariableTypeNode> assignmentTypeQualifier, std::shared_ptr<ASTIdentifierNode> astIdentifierNode) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
    _children.push_back(_assignmentTypeQualifier);
    _children.push_back(_identifier);
}

std::shared_ptr<ASTVariableTypeNode> ASTVariableDefinitionNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

std::shared_ptr<ASTIdentifierNode> ASTVariableDefinitionNode::getIdentifierNode() {
    return _identifier;
}

std::shared_ptr<Position> ASTVariableDefinitionNode::getStartPosition() {
    return _assignmentTypeQualifier->getStartPosition();
}

std::shared_ptr<Position> ASTVariableDefinitionNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTVariableDefinitionNode::getNodeType() {
    return AST_VARIABLE_DEFINITION_NODE;
}

std::string ASTVariableDefinitionNode::toString() {
    return "VARIABLE_DEFINITION";
}

bool ASTVariableDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTVariableDefinitionNode>(other);

    return this->getVarTypeNode()->isSameAs(otherNode->getVarTypeNode()) &&
           this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignmentTypeQualifier->print();
    _identifier->print();
    Logger::log("----------");
}

std::string ASTVariableDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignmentTypeQualifier)->add(_identifier);
    return sourceCodeBuilder.build();
}
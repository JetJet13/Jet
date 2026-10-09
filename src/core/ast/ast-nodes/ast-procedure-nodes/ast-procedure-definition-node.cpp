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
// Created by Johny Georges on 2024-10-25.
//

#include "ast-procedure-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureDefinitionNode::ASTProcedureDefinitionNode(std::shared_ptr<ASTProcedureNode> functionKeyword, std::shared_ptr<ASTFunctionNameNode> name, std::shared_ptr<ASTFunctionParameterListNode> parameters) {
    _procedureKeyword = functionKeyword;
    _name = name;
    _parameters = parameters;
    _children.push_back(_procedureKeyword);
    _children.push_back(_name);
    _children.push_back(_parameters);
}

std::shared_ptr<ASTFunctionParameterListNode> ASTProcedureDefinitionNode::getParameters() {
    return _parameters;
}

std::shared_ptr<ASTFunctionNameNode> ASTProcedureDefinitionNode::getName() {
    return _name;
}

uint64_t ASTProcedureDefinitionNode::numParameters() {
    return _parameters->numParameters();
}

std::shared_ptr<Position> ASTProcedureDefinitionNode::getStartPosition() {
    return _procedureKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTProcedureDefinitionNode::getEndPosition() {
    return _parameters->getEndPosition();
}

ASTNodeType ASTProcedureDefinitionNode::getNodeType() {
    return AST_PROCEDURE_DEFINITION_NODE;
}

std::string ASTProcedureDefinitionNode::toString() {
    return "PROCEDURE_DEFINITION";
}

bool ASTProcedureDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTProcedureDefinitionNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters());
}

void ASTProcedureDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    Logger::log("----------");
}

std::string ASTProcedureDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_procedureKeyword);
    sourceCodeBuilder.add(_name)
    ->add(_parameters);
    return sourceCodeBuilder.build();
}
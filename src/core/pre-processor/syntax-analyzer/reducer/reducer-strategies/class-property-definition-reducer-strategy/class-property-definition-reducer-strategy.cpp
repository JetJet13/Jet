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
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"

std::shared_ptr<ASTNode> ClassPropertyDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() < 2 || nodes.size() > 4) {
        throw std::invalid_argument("unable to reduce to class property definition since nodes list size is < 2 or > 4");
    }

    return std::make_shared<ASTClassPropertyDefinitionNode>(
            std::dynamic_pointer_cast<ASTAccessModifierNode>(nodes[0]),
            this->getPropertyName(&nodes),
            this->getStatic(&nodes),
            this->getConstant(&nodes)
    );
}

std::shared_ptr<ASTClassPropertyNameNode> ClassPropertyDefinitionReducerStrategy::getPropertyName(std::vector<std::shared_ptr<ASTNode>>* nodes) {
    if (nodes->size() == 4 && nodes->at(3)->is(AST_IDENTIFIER_NODE)) {
        auto idNode = std::dynamic_pointer_cast<ASTIdentifierNode>(nodes->at(3));
        auto classPropertyName = std::make_shared<ASTClassPropertyNameNode>(idNode->getLexeme());
        classPropertyName->setId(idNode->getId());
        return classPropertyName;
    } else if (nodes->size() == 3 && nodes->at(2)->is(AST_IDENTIFIER_NODE)) {
        auto idNode = std::dynamic_pointer_cast<ASTIdentifierNode>(nodes->at(2));
        auto classPropertyName = std::make_shared<ASTClassPropertyNameNode>(idNode->getLexeme());
        classPropertyName->setId(idNode->getId());
        return classPropertyName;
    } else {
        auto idNode = std::dynamic_pointer_cast<ASTIdentifierNode>(nodes->at(1));
        auto classPropertyName = std::make_shared<ASTClassPropertyNameNode>(idNode->getLexeme());
        classPropertyName->setId(idNode->getId());
        return classPropertyName;
    }
}

std::optional<std::shared_ptr<ASTStaticNode>> ClassPropertyDefinitionReducerStrategy::getStatic(std::vector<std::shared_ptr<ASTNode>>* nodes) {
    if (nodes->at(1)->is(AST_STATIC_NODE)) {
        return std::dynamic_pointer_cast<ASTStaticNode>(nodes->at(1));
    }
    return {};
}

std::optional<std::shared_ptr<ASTConstNode>> ClassPropertyDefinitionReducerStrategy::getConstant(std::vector<std::shared_ptr<ASTNode>>* nodes) {
    if (nodes->size() > 2) {
        if (nodes->at(1)->is(AST_CONST_NODE)) {
            return std::dynamic_pointer_cast<ASTConstNode>(nodes->at(1));
        } else if (nodes->at(2)->is(AST_CONST_NODE)) {
            return std::dynamic_pointer_cast<ASTConstNode>(nodes->at(2));
        }
    }
    return {};
}
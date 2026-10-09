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
// Created by Johny Georges on 2024-05-02.
//

#include "class-constructor-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../../shared/utils/to-string/to-string.h"

void ClassConstructorDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto classConstructorDeclarationNode = std::dynamic_pointer_cast<ASTClassConstructorDeclarationNode>(node);
    auto classDeclarationNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(classConstructorDeclarationNode->getParentNode().value());
    auto className = _tokenTable->getIdentifier(
            classDeclarationNode->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
    );

    classConstructorDeclarationNode->setId(className +
            "_constructor_" +
            ToStringUtil::toString(
                classConstructorDeclarationNode
                ->getConstructor()
                ->getLexeme()
                ->getStartPosition()
                ->getLine()
            ) +
            "_" +
            ToStringUtil::toString(
                classConstructorDeclarationNode
                ->getConstructor()
                ->getLexeme()
                ->getStartPosition()
                ->getColumn()
            ));
}
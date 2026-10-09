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
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

void CustomTypeDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto customTypeDeclarationNode = std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(node);
    customTypeDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    customTypeDeclarationNode
                            ->getName()
                            ->getLexeme()
                            ->getToken()
                            ->getValueId()
                            .value()
            )
    );
}
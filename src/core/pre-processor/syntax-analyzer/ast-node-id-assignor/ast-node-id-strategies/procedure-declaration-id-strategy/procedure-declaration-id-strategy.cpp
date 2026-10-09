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

#include "procedure-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

void ProcedureDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto procedureDeclarationNode = std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node);
    procedureDeclarationNode->setId(
            _tokenTable->getIdentifier(
                procedureDeclarationNode
                ->getName()
                ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}
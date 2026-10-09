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
// Created by Johny Georges on 2024-05-13.
//

#include "access-modifier-type-signature-strategy.h"

void AccessModifierTypeSignatureStrategy::assign(std::shared_ptr<ASTAccessModifierNode> accessModifierNode) {
    switch (accessModifierNode->getNodeType()) {
        case AST_PUBLIC_NODE:
            accessModifierNode->setTypeSignature(std::make_shared<AccessModifierTypeSignature>(PUBLIC_ACCESS_MODIFIER_TYPE));
            break;
        case AST_PROTECTED_NODE:
            accessModifierNode->setTypeSignature(std::make_shared<AccessModifierTypeSignature>(PROTECTED_ACCESS_MODIFIER_TYPE));
            break;
        case AST_PRIVATE_NODE:
            accessModifierNode->setTypeSignature(std::make_shared<AccessModifierTypeSignature>(PRIVATE_ACCESS_MODIFIER_TYPE));
            break;
        default:
            throw std::invalid_argument("unknown access modifier type");
    }
}
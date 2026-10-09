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
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_TYPE_DECLARATION_NODE_H
#define JETLANG_AST_TYPE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"

class ASTTypeDeclarationNode : public ASTNode {
protected:
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    virtual void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
};

#endif //JETLANG_AST_TYPE_DECLARATION_NODE_H

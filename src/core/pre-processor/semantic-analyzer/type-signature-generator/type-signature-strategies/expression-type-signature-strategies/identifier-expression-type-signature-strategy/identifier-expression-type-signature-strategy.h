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
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../type-signature-context.h"

class IdentifierExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTIdentifierExpressionNode> identifierExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

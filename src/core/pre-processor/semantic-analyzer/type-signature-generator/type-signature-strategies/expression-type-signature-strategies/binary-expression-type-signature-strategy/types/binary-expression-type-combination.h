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
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H
#define JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

#include "../../../../../../../type-signature/types/type-source.h"
#include "../../../../../../../symbol/types/symbol-type.h"
#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../../../../../type-signature/type-signature.h"

struct BinaryComboResultType;

class BinaryExpressionTypeCombination {
private:
    std::shared_ptr<Symbol> _operatorSymbol;
    std::vector<BinaryComboResultType> _binaryResultTypes;
public:
    BinaryExpressionTypeCombination(std::shared_ptr<Symbol> operatorSymbol, std::vector<BinaryComboResultType> binaryResultTypes);
    std::shared_ptr<Symbol> getOperator();
    std::optional<std::shared_ptr<TypeSignature>> match(std::shared_ptr<TypeSignature> leftTypeSignature, std::shared_ptr<TypeSignature> rightTypeSignature);
};

struct BinaryComboResultType {
    TypeSource leftType;
    TypeSource rightType;
    std::shared_ptr<TypeSignature> resultType;
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

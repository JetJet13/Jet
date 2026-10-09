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

#include "binary-expression-type-combination.h"


BinaryExpressionTypeCombination::BinaryExpressionTypeCombination(std::shared_ptr<Symbol> operatorSymbol, std::vector<BinaryComboResultType> binaryResultTypes) {
    _operatorSymbol = operatorSymbol;
    _binaryResultTypes = std::move(binaryResultTypes);
}

std::shared_ptr<Symbol> BinaryExpressionTypeCombination::getOperator() {
    return _operatorSymbol;
}

std::optional<std::shared_ptr<TypeSignature>> BinaryExpressionTypeCombination::match(std::shared_ptr<TypeSignature> leftTypeSignature, std::shared_ptr<TypeSignature> rightTypeSignature) {
    for (auto binaryResultType: _binaryResultTypes) {
        if ((leftTypeSignature->typeTargetIs(binaryResultType.leftType) &&
             rightTypeSignature->typeTargetIs(binaryResultType.rightType)) ||
            (leftTypeSignature->typeTargetIs(binaryResultType.rightType) &&
             rightTypeSignature->typeTargetIs(binaryResultType.leftType))) {
            return binaryResultType.resultType;
        }
    }
    return {};
}


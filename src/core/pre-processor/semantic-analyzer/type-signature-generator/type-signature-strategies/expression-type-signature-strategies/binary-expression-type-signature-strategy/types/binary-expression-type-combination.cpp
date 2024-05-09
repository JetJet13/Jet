//
// Created by Johny Georges on 2024-05-06.
//

#include "binary-expression-type-combination.h"


BinaryExpressionTypeCombination::BinaryExpressionTypeCombination(Symbol* operatorSymbol, std::vector<BinaryComboResultType> binaryResultTypes) {
    _operatorSymbol = operatorSymbol;
    _binaryResultTypes = std::move(binaryResultTypes);
}

Symbol* BinaryExpressionTypeCombination::getOperator() {
    return _operatorSymbol;
}

std::optional<TypeSignature*> BinaryExpressionTypeCombination::match(TypeSignature* leftTypeSignature, TypeSignature* rightTypeSignature) {
    for (auto binaryResultType: _binaryResultTypes) {
        if ((leftTypeSignature->hasTypeSource(binaryResultType.leftType) && rightTypeSignature->hasTypeSource(binaryResultType.rightType)) ||
            (leftTypeSignature->hasTypeSource(binaryResultType.rightType) && rightTypeSignature->hasTypeSource(binaryResultType.leftType))) {
            return binaryResultType.resultType;
        }
    }
    return {};
}


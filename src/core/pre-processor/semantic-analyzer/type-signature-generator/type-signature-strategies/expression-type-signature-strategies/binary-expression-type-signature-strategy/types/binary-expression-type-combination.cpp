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
        if ((leftTypeSignature->typeTargetIs(binaryResultType.leftType) &&
             rightTypeSignature->typeTargetIs(binaryResultType.rightType)) ||
            (leftTypeSignature->typeTargetIs(binaryResultType.rightType) &&
             rightTypeSignature->typeTargetIs(binaryResultType.leftType))) {
            return binaryResultType.resultType;
        }
    }
    return {};
}


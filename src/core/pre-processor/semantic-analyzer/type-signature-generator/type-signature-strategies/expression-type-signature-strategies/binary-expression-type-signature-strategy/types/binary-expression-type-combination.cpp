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


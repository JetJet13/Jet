//
// Created by Johny Georges on 2024-05-06.
//

#include "binary-expression-type-signature-strategy.h"
#include "../../../../../../symbol/symbol-factory.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

BinaryExpressionTypeSignatureStrategy::BinaryExpressionTypeSignatureStrategy() {
    this->initCombinations();
}

TypeSignature* BinaryExpressionTypeSignatureStrategy::create(ASTBinaryExpressionNode* binaryExpression, TypeSignatureStrategyProvider* strategyMap) {
    auto leftTypeSignature = strategyMap->getTypeSignatureForExpression(binaryExpression->getLeftNode());
    auto rightTypeSignature = strategyMap->getTypeSignatureForExpression(binaryExpression->getRightNode());
    auto combination = this->findCombination(binaryExpression->getBinaryOperator());
    if (!combination) {
        throw std::invalid_argument("unknown binary operator..aborting.");
    }

    auto resultTypeSignature = combination.value()->match(leftTypeSignature, rightTypeSignature);
    if (!resultTypeSignature) {
        return new InvalidTypeSignature();
    }
    return resultTypeSignature.value();
}

std::optional<BinaryExpressionTypeCombination*> BinaryExpressionTypeSignatureStrategy::findCombination(ASTBinaryOperatorNode* binaryOperatorNode) {
    for (auto combination : _combinations) {
        if (binaryOperatorNode->getOperator()->getToken()->getSymbol()->isSameAs(combination->getOperator())) {
            return combination;
        }
    }
    return {};
}

void BinaryExpressionTypeSignatureStrategy::initCombinations() {
    _combinations = std::vector<BinaryExpressionTypeCombination*>({
        new BinaryExpressionTypeCombination(SymbolFactory::createPlusSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { STRING_LITERAL_TYPE_SOURCE, STRING_LITERAL_TYPE_SOURCE, new StringLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createMinusSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { STRING_LITERAL_TYPE_SOURCE, STRING_LITERAL_TYPE_SOURCE, new StringLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createStarSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createSlashSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createModuloSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createEqualEqualSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { STRING_LITERAL_TYPE_SOURCE, STRING_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { BOOL_LITERAL_TYPE_SOURCE, BOOL_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createGreaterThanSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createLessThanSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createGreaterThanOrEqualSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createLessThanOrEqualSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { INT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),

    });
}
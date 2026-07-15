//
// Created by Johny Georges on 2024-05-06.
//

#include "binary-expression-type-signature-strategy.h"
#include "../../../../../../symbol/symbol-factory.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

BinaryExpressionTypeSignatureStrategy::BinaryExpressionTypeSignatureStrategy() {
    this->initCombinations();
}

void BinaryExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTBinaryArithmeticExpressionNode> binaryExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(binaryExpression->getLeftNode(), context, scope);
    strategyMap->assignTypeSignatureFor(binaryExpression->getRightNode(), context, scope);
    auto combination = this->findCombination(binaryExpression->getBinaryOperator());
    if (!combination) {
        throw std::invalid_argument("unknown binary arithmetic operator..aborting.");
    }

    auto leftNodeTypeSignature = binaryExpression->getLeftNode()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)
                                    ? (std::dynamic_pointer_cast<SharedTypeSignature>(binaryExpression->getLeftNode()->getTypeSignature())->getUnderlyingType())
                                    : binaryExpression->getLeftNode()->getTypeSignature()->getTargetTypeSignature();

    auto rightNodeTypeSignature = binaryExpression->getRightNode()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)
                                    ? (std::dynamic_pointer_cast<SharedTypeSignature>(binaryExpression->getRightNode()->getTypeSignature())->getUnderlyingType())
                                    : binaryExpression->getRightNode()->getTypeSignature()->getTargetTypeSignature();


    auto resultTypeSignature = combination.value()->match(
            leftNodeTypeSignature,
            rightNodeTypeSignature
    );
    if (!resultTypeSignature) {
        binaryExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }
    binaryExpression->setLeftTypeSignature(leftNodeTypeSignature);
    binaryExpression->setRightTypeSignature(rightNodeTypeSignature);
    binaryExpression->setTypeSignature(resultTypeSignature.value());
}

void BinaryExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTBinaryComparatorExpressionNode> binaryExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(binaryExpression->getLeftNode(), context, scope);
    strategyMap->assignTypeSignatureFor(binaryExpression->getRightNode(), context, scope);
    auto combination = this->findCombination(binaryExpression->getBinaryOperator());
    if (!combination) {
        throw std::invalid_argument("unknown binary comparator operator..aborting.");
    }

    auto leftNodeTypeSignature = binaryExpression->getLeftNode()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)
                                 ? (std::dynamic_pointer_cast<SharedTypeSignature>(binaryExpression->getLeftNode()->getTypeSignature())->getUnderlyingType())
                                 : binaryExpression->getLeftNode()->getTypeSignature()->getTargetTypeSignature();

    auto rightNodeTypeSignature = binaryExpression->getRightNode()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)
                                  ? (std::dynamic_pointer_cast<SharedTypeSignature>(binaryExpression->getRightNode()->getTypeSignature())->getUnderlyingType())
                                  : binaryExpression->getRightNode()->getTypeSignature()->getTargetTypeSignature();


    auto resultTypeSignature = combination.value()->match(
            leftNodeTypeSignature,
            rightNodeTypeSignature
    );
    if (!resultTypeSignature) {
        binaryExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }
    binaryExpression->setLeftTypeSignature(leftNodeTypeSignature);
    binaryExpression->setRightTypeSignature(rightNodeTypeSignature);
    binaryExpression->setTypeSignature(resultTypeSignature.value());
}

std::optional<std::shared_ptr<BinaryExpressionTypeCombination>> BinaryExpressionTypeSignatureStrategy::findCombination(std::shared_ptr<ASTBinaryArithmeticOperatorNode> binaryOperatorNode) {
    for (auto combination : _arithmeticCombinations) {
        if (binaryOperatorNode->getOperator()->getToken()->getSymbol()->isSameAs(combination->getOperator())) {
            return combination;
        }
    }
    return {};
}

std::optional<std::shared_ptr<BinaryExpressionTypeCombination>> BinaryExpressionTypeSignatureStrategy::findCombination(std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperatorNode) {
    for (auto combination : _comparatorCombinations) {
        if (binaryOperatorNode->getOperator()->getToken()->getSymbol()->isSameAs(combination->getOperator())) {
            return combination;
        }
    }
    return {};
}

void BinaryExpressionTypeSignatureStrategy::initCombinations() {
    _arithmeticCombinations = std::vector<std::shared_ptr<BinaryExpressionTypeCombination>>({
        std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createPlusSymbol(), std::vector<BinaryComboResultType> {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, std::make_shared<IntLiteralTypeSignature>() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<FloatLiteralTypeSignature>() },
        }),
        std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createMinusSymbol(), std::vector<BinaryComboResultType> {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, std::make_shared<IntLiteralTypeSignature>() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<FloatLiteralTypeSignature>() },
        }),
        std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createStarSymbol(), std::vector<BinaryComboResultType> {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, std::make_shared<IntLiteralTypeSignature>() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<FloatLiteralTypeSignature>() },
        }),
        std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createSlashSymbol(), std::vector<BinaryComboResultType> {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, std::make_shared<IntLiteralTypeSignature>() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<FloatLiteralTypeSignature>() },
        }),
        std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createModuloSymbol(), std::vector<BinaryComboResultType> {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, std::make_shared<IntLiteralTypeSignature>() },
        }),
    });

    _comparatorCombinations = std::vector<std::shared_ptr<BinaryExpressionTypeCombination>>({
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createEqualEqualSymbol(), std::vector<BinaryComboResultType> {
                    {INT_LITERAL_TYPE_SOURCE,        INT_LITERAL_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {FLOAT_LITERAL_TYPE_SOURCE,      FLOAT_LITERAL_TYPE_SOURCE,      std::make_shared<BoolLiteralTypeSignature>() },
                    {CHAR_LITERAL_TYPE_SOURCE,       CHAR_LITERAL_TYPE_SOURCE,       std::make_shared<BoolLiteralTypeSignature>() },
                    {STRING_LITERAL_TYPE_SOURCE,     STRING_LITERAL_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {BOOL_LITERAL_TYPE_SOURCE,       BOOL_LITERAL_TYPE_SOURCE,       std::make_shared<BoolLiteralTypeSignature>() },
                    {ARRAY_TYPE_SOURCE,              ARRAY_TYPE_SOURCE,              std::make_shared<BoolLiteralTypeSignature>() },
                    {STRUCT_TYPE_SOURCE,             STRUCT_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {TUPLE_TYPE_SOURCE,              TUPLE_TYPE_SOURCE,              std::make_shared<BoolLiteralTypeSignature>() },
                    {SHARED_TYPE_SOURCE,             SHARED_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {CLASS_INSTANCE_TYPE_SOURCE,     CLASS_INSTANCE_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {NEW_CLASS_INSTANCE_TYPE_SOURCE, NEW_CLASS_INSTANCE_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    {CLASS_INSTANCE_TYPE_SOURCE,     NEW_CLASS_INSTANCE_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    {NEW_CLASS_INSTANCE_TYPE_SOURCE, CLASS_INSTANCE_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_TYPE_SOURCE,             LAMBDA_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_EXPRESSION_TYPE_SOURCE,  std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_TYPE_SOURCE,             LAMBDA_EXPRESSION_TYPE_SOURCE,  std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_TYPE_SOURCE,               ENUM_TYPE_SOURCE,               std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_TYPE_SOURCE,               ENUM_ACCESS_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_ACCESS_TYPE_SOURCE,        ENUM_ACCESS_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_ACCESS_TYPE_SOURCE,        ENUM_TYPE_SOURCE,               std::make_shared<BoolLiteralTypeSignature>() },
            }),
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createBangEqualSymbol(), std::vector<BinaryComboResultType> {
                    {INT_LITERAL_TYPE_SOURCE,        INT_LITERAL_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {FLOAT_LITERAL_TYPE_SOURCE,      FLOAT_LITERAL_TYPE_SOURCE,      std::make_shared<BoolLiteralTypeSignature>() },
                    {CHAR_LITERAL_TYPE_SOURCE,       CHAR_LITERAL_TYPE_SOURCE,       std::make_shared<BoolLiteralTypeSignature>() },
                    {STRING_LITERAL_TYPE_SOURCE,     STRING_LITERAL_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {BOOL_LITERAL_TYPE_SOURCE,       BOOL_LITERAL_TYPE_SOURCE,       std::make_shared<BoolLiteralTypeSignature>() },
                    {ARRAY_TYPE_SOURCE,              ARRAY_TYPE_SOURCE,              std::make_shared<BoolLiteralTypeSignature>() },
                    {STRUCT_TYPE_SOURCE,             STRUCT_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {TUPLE_TYPE_SOURCE,              TUPLE_TYPE_SOURCE,              std::make_shared<BoolLiteralTypeSignature>() },
                    {SHARED_TYPE_SOURCE,             SHARED_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {CLASS_INSTANCE_TYPE_SOURCE,     CLASS_INSTANCE_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {NEW_CLASS_INSTANCE_TYPE_SOURCE, NEW_CLASS_INSTANCE_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    {CLASS_INSTANCE_TYPE_SOURCE,     NEW_CLASS_INSTANCE_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    {NEW_CLASS_INSTANCE_TYPE_SOURCE, CLASS_INSTANCE_TYPE_SOURCE,     std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_TYPE_SOURCE,             LAMBDA_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_EXPRESSION_TYPE_SOURCE,  std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_TYPE_SOURCE,             LAMBDA_EXPRESSION_TYPE_SOURCE,  std::make_shared<BoolLiteralTypeSignature>() },
                    {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_TYPE_SOURCE,             std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_TYPE_SOURCE,               ENUM_TYPE_SOURCE,               std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_TYPE_SOURCE,               ENUM_ACCESS_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_ACCESS_TYPE_SOURCE,        ENUM_ACCESS_TYPE_SOURCE,        std::make_shared<BoolLiteralTypeSignature>() },
                    {ENUM_ACCESS_TYPE_SOURCE,        ENUM_TYPE_SOURCE,               std::make_shared<BoolLiteralTypeSignature>() },
            }),
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createGreaterThanSymbol(), std::vector<BinaryComboResultType> {
                    { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
            }),
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createLessThanSymbol(), std::vector<BinaryComboResultType> {
                    { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
            }),
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createGreaterThanOrEqualSymbol(), std::vector<BinaryComboResultType> {
                    { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
            }),
            std::make_shared<BinaryExpressionTypeCombination>(SymbolFactory::createLessThanOrEqualSymbol(), std::vector<BinaryComboResultType> {
                    { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
                    { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, std::make_shared<BoolLiteralTypeSignature>() },
            }),
    });
}
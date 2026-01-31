//
// Created by Johny Georges on 2024-05-06.
//

#include "binary-expression-type-signature-strategy.h"
#include "../../../../../../symbol/symbol-factory.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

BinaryExpressionTypeSignatureStrategy::BinaryExpressionTypeSignatureStrategy() {
    this->initCombinations();
}

void BinaryExpressionTypeSignatureStrategy::assign(ASTBinaryExpressionNode* binaryExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(binaryExpression->getLeftNode(), scope);
    strategyMap->assignTypeSignatureFor(binaryExpression->getRightNode(), scope);
    auto combination = this->findCombination(binaryExpression->getBinaryOperator());
    if (!combination) {
        throw std::invalid_argument("unknown binary operator..aborting.");
    }

    auto leftNodeTypeSignature = binaryExpression->getLeftNode()->getTypeSignature()->typeTargetIs(REF_TYPE_SOURCE) ?
                                 ((RefTypeSignature*)binaryExpression->getLeftNode()->getTypeSignature())->getUnderlyingType() :
                                 binaryExpression->getLeftNode()->getTypeSignature()->getTargetTypeSignature();

    auto rightNodeTypeSignature = binaryExpression->getRightNode()->getTypeSignature()->typeTargetIs(REF_TYPE_SOURCE) ?
                                 ((RefTypeSignature*)binaryExpression->getRightNode()->getTypeSignature())->getUnderlyingType() :
                                 binaryExpression->getRightNode()->getTypeSignature()->getTargetTypeSignature();

    auto resultTypeSignature = combination.value()->match(
            leftNodeTypeSignature,
            rightNodeTypeSignature
    );
    if (!resultTypeSignature) {
        binaryExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }
    binaryExpression->setTypeSignature(resultTypeSignature.value());
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
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createMinusSymbol(), {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createStarSymbol(), {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createSlashSymbol(), {
                { INT_LITERAL_TYPE_SOURCE,   INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new FloatLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createModuloSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new IntLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createEqualEqualSymbol(), {
                {INT_LITERAL_TYPE_SOURCE,        INT_LITERAL_TYPE_SOURCE,        new BoolLiteralTypeSignature() },
                {FLOAT_LITERAL_TYPE_SOURCE,      FLOAT_LITERAL_TYPE_SOURCE,      new BoolLiteralTypeSignature() },
                {CHAR_LITERAL_TYPE_SOURCE,       CHAR_LITERAL_TYPE_SOURCE,       new BoolLiteralTypeSignature() },
                {STRING_LITERAL_TYPE_SOURCE,     STRING_LITERAL_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {BOOL_LITERAL_TYPE_SOURCE,       BOOL_LITERAL_TYPE_SOURCE,       new BoolLiteralTypeSignature() },
                {ARRAY_TYPE_SOURCE,              ARRAY_TYPE_SOURCE,              new BoolLiteralTypeSignature() },
                {STRUCT_TYPE_SOURCE,             STRUCT_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
                {TUPLE_TYPE_SOURCE,              TUPLE_TYPE_SOURCE,              new BoolLiteralTypeSignature() },
                {REF_TYPE_SOURCE,                REF_TYPE_SOURCE,                new BoolLiteralTypeSignature() },
                {CLASS_INSTANCE_TYPE_SOURCE,     CLASS_INSTANCE_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {NEW_CLASS_INSTANCE_TYPE_SOURCE, NEW_CLASS_INSTANCE_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                {CLASS_INSTANCE_TYPE_SOURCE,     NEW_CLASS_INSTANCE_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                {NEW_CLASS_INSTANCE_TYPE_SOURCE, CLASS_INSTANCE_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {LAMBDA_TYPE_SOURCE,             LAMBDA_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
                {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_EXPRESSION_TYPE_SOURCE,  new BoolLiteralTypeSignature() },
                {LAMBDA_TYPE_SOURCE,             LAMBDA_EXPRESSION_TYPE_SOURCE,  new BoolLiteralTypeSignature() },
                {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createBangEqualSymbol(), {
                {INT_LITERAL_TYPE_SOURCE,        INT_LITERAL_TYPE_SOURCE,        new BoolLiteralTypeSignature() },
                {FLOAT_LITERAL_TYPE_SOURCE,      FLOAT_LITERAL_TYPE_SOURCE,      new BoolLiteralTypeSignature() },
                {CHAR_LITERAL_TYPE_SOURCE,       CHAR_LITERAL_TYPE_SOURCE,       new BoolLiteralTypeSignature() },
                {STRING_LITERAL_TYPE_SOURCE,     STRING_LITERAL_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {BOOL_LITERAL_TYPE_SOURCE,       BOOL_LITERAL_TYPE_SOURCE,       new BoolLiteralTypeSignature() },
                {ARRAY_TYPE_SOURCE,              ARRAY_TYPE_SOURCE,              new BoolLiteralTypeSignature() },
                {STRUCT_TYPE_SOURCE,             STRUCT_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
                {TUPLE_TYPE_SOURCE,              TUPLE_TYPE_SOURCE,              new BoolLiteralTypeSignature() },
                {REF_TYPE_SOURCE,                REF_TYPE_SOURCE,                new BoolLiteralTypeSignature() },
                {CLASS_INSTANCE_TYPE_SOURCE,     CLASS_INSTANCE_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {NEW_CLASS_INSTANCE_TYPE_SOURCE, NEW_CLASS_INSTANCE_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                {CLASS_INSTANCE_TYPE_SOURCE,     NEW_CLASS_INSTANCE_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                {NEW_CLASS_INSTANCE_TYPE_SOURCE, CLASS_INSTANCE_TYPE_SOURCE,     new BoolLiteralTypeSignature() },
                {LAMBDA_TYPE_SOURCE,             LAMBDA_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
                {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_EXPRESSION_TYPE_SOURCE,  new BoolLiteralTypeSignature() },
                {LAMBDA_TYPE_SOURCE,             LAMBDA_EXPRESSION_TYPE_SOURCE,  new BoolLiteralTypeSignature() },
                {LAMBDA_EXPRESSION_TYPE_SOURCE,  LAMBDA_TYPE_SOURCE,             new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createGreaterThanSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createLessThanSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createGreaterThanOrEqualSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
        new BinaryExpressionTypeCombination(SymbolFactory::createLessThanOrEqualSymbol(), {
                { INT_LITERAL_TYPE_SOURCE, INT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { FLOAT_LITERAL_TYPE_SOURCE, FLOAT_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
                { CHAR_LITERAL_TYPE_SOURCE, CHAR_LITERAL_TYPE_SOURCE, new BoolLiteralTypeSignature() },
        }),
    });
}
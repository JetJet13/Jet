//
// Created by Johny Georges on 2024-06-07.
//

#ifndef JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class LambdaWithFatArrowExpressionTypeSignatureStrategy {
public:
    void assign(ASTLambdaWithFatArrowExpressionNode* lambdaWithFatArrowExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LAMBDA_WITH_FAT_ARROW_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

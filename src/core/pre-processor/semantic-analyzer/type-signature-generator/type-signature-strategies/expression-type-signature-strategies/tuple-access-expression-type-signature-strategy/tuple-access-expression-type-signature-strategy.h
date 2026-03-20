//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"

class TupleAccessExpressionTypeSignatureStrategy {
public:
    void assign(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

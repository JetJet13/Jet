//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_TUPLE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H


#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class TupleExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTTupleExpressionNode* node, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

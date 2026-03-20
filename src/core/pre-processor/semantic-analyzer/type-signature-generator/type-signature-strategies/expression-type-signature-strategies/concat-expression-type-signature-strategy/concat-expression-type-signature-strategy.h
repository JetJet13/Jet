//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_CONCAT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CONCAT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class ConcatExpressionTypeSignatureStrategy {
public:
    void assign(ASTConcatExpressionNode* concatExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CONCAT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

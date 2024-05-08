//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_CURRY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CURRY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-curry-expression-node.h"
#include "../../../../../../../type-signature/type-signature.h"
#include "../../expression-type-signature-strategy-provider.h"

class CurryExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTCurryExpressionNode* curryExpression, ExpressionTypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CURRY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

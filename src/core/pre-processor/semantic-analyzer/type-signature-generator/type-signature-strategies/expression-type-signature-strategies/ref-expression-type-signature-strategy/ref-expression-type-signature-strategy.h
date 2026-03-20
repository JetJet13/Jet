//
// Created by Johny Georges on 2025-02-01.
//

#ifndef JETLANG_REF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_REF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

class RefExpressionTypeSignatureStrategy {
public:
    void assign(ASTRefExpressionNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_REF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

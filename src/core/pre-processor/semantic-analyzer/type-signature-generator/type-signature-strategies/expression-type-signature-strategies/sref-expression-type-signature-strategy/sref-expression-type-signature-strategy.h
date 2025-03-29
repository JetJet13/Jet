//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_SREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_SREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-sref-expression-node.h"

class SrefExpressionTypeSignatureStrategy {
public:
    void assign(ASTSrefExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_SREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

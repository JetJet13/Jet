//
// Created by Johny Georges on 2025-02-01.
//

#ifndef JETLANG_DREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_DREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

class DrefExpressionTypeSignatureStrategy {
public:
    void assign(ASTDrefExpressionNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_DREF_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

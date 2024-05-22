//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_LOGICAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LOGICAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class LogicalExpressionTypeSignatureStrategy {
public:
    void assign(ASTLogicalExpressionNode* logicalExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LOGICAL_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

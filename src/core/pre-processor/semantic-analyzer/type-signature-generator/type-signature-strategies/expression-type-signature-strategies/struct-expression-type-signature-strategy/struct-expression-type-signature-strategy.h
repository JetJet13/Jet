//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_STRUCT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class StructExpressionTypeSignatureStrategy {
public:
    void assign(ASTStructExpressionNode* structExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_STRUCT_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

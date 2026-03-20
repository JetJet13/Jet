//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"

class NewClassInstanceExpressionTypeSignatureStrategy {
public:
    void assign(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureContext* context, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

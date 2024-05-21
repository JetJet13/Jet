//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class NewClassInstanceExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

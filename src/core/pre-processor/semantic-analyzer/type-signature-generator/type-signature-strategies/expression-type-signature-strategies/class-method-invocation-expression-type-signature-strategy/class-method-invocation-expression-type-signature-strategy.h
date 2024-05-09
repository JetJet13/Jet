//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"


class ClassMethodInvocationExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable);
};

#endif //JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

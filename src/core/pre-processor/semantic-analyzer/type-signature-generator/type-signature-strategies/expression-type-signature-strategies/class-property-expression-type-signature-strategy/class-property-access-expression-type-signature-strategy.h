//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../type-signature-context.h"


class ClassPropertyAccessExpressionTypeSignatureStrategy {
public:
    void assign(ASTClassPropertyAccessExpressionNode* classPropertyExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

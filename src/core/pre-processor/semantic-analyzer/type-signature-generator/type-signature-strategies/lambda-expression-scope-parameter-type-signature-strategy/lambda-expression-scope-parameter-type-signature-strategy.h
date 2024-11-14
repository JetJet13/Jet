//
// Created by Johny Georges on 2024-11-11.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../../../../type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"

class LambdaExpressionScopeParameterTypeSignatureStrategy {
public:
    ParameterListItemTypeSignature* create(TypeSignatureLookupTable* scope);
};


#endif //JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H

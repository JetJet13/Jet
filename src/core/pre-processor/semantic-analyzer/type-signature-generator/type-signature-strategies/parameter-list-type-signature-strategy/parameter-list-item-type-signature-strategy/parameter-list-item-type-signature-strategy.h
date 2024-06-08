//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../type-signature-strategy-provider.h"

class ParameterListItemTypeSignatureStrategy {
public:
    void assignAndAddToScope(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_STRATEGY_H

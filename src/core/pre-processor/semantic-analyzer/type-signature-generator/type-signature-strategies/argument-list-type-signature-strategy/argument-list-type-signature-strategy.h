//
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H

#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"

class ArgumentListTypeSignatureStrategy {
public:
    void assign(ASTFunctionArgumentListNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H

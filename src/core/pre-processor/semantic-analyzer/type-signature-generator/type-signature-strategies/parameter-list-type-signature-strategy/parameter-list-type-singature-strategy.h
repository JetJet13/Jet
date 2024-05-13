//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H
#define JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"
#include "../type-signature-strategy-provider.h"

class ParameterListTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionParameterListNode* node, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SINGATURE_STRATEGY_H

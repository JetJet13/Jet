//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_CONDITION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CONDITION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-condition-node.h"

class ConditionTypeSignatureStrategy {
public:
    void assign(ASTControlFlowConditionNode* controlFlowConditionNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_CONDITION_TYPE_SIGNATURE_STRATEGY_H

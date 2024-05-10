//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_THIS_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_THIS_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-this-type-node.h"
#include "../../../type-signature-strategy-provider.h"

class ThisTypeTypeSignatureStrategy {
public:
    TypeSignature* create(ASTThisTypeNode* node, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_THIS_TYPE_TYPE_SIGNATURE_STRATEGY_H

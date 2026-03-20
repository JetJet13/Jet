//
// Created by Johny Georges on 2025-02-08.
//

#ifndef JETLANG_REF_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_REF_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-ref-type-node.h"
#include "../../../type-signature-strategy-provider.h"

class RefTypeTypeSignatureStrategy {
public:
    void assign(ASTRefTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_REF_TYPE_TYPE_SIGNATURE_STRATEGY_H

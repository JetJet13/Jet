//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARED_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_SHARED_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-shared-type-node.h"
#include "../../../type-signature-strategy-provider.h"

class SharedTypeTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTSharedTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_SHARED_TYPE_TYPE_SIGNATURE_STRATEGY_H

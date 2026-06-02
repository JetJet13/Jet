//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_MODULE_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_MODULE_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-module-type-nodes/ast-module-type-node.h"

class ModuleTypeTypeSignatureStrategy {
public:
    void assign(ASTModuleTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_MODULE_TYPE_TYPE_SIGNATURE_STRATEGY_H

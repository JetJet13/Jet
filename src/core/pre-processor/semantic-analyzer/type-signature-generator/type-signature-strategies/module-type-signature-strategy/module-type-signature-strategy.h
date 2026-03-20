//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_MODULE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

class ModuleTypeSignatureStrategy {
public:
    void assign(ASTModuleDeclarationNode* moduleDeclarationNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
    void assignInitial(ASTModuleDeclarationNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_MODULE_TYPE_SIGNATURE_STRATEGY_H

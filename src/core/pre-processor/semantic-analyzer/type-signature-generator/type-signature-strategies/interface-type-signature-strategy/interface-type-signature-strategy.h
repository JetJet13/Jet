//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_INTERFACE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_INTERFACE_TYPE_SIGNATURE_STRATEGY_H

#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

class InterfaceTypeSignatureStrategy {
public:
    void assign(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_INTERFACE_TYPE_SIGNATURE_STRATEGY_H

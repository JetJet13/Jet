//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-property-node.h"

class InterfacePropertyTypeSignatureStrategy {
public:
    void assign(ASTInterfacePropertyNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_STRATEGY_H

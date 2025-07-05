//
// Created by Johny Georges on 2025-07-04.
//

#ifndef JETLANG_INTERFACE_TYPE_DECLARATION_IR_STRATEGY_H
#define JETLANG_INTERFACE_TYPE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-type-declaration-nodes/ir-interface-type-declaration-node.h"

class InterfaceTypeDeclarationIRStrategy {
public:
    IRInterfaceTypeDeclarationNode* generate(ASTInterfaceTypeDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_INTERFACE_TYPE_DECLARATION_IR_STRATEGY_H

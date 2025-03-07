//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H
#define JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../ir-injector.h"


class VariableIRInjectorStrategy {
private:
    IROperationType determineOperationType(IRVariableDeclarationNode* irVariableDeclaration);
public:
    void inject(IRVariableDeclarationNode* irVariableDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H

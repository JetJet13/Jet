//
// Created by Johny Georges on 2024-10-31.
//

#ifndef JETLANG_MODULE_IR_INJECTOR_STRATEGY_H
#define JETLANG_MODULE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class ModuleIRInjectorStrategy {
public:
    void inject(IRModuleDeclarationNode* irModuleDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_MODULE_IR_INJECTOR_STRATEGY_H

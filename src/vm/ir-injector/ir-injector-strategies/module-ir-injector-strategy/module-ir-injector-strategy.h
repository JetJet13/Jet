//
// Created by Johny Georges on 2024-10-31.
//

#ifndef JETLANG_MODULE_IR_INJECTOR_STRATEGY_H
#define JETLANG_MODULE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class ModuleIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRModuleDeclarationNode> irModuleDeclaration, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_MODULE_IR_INJECTOR_STRATEGY_H

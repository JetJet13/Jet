//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_MODULE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_MODULE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-module-access-assignment-statement-node.h"

class ModuleAccessAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRModuleAccessAssignmentStatementNode> irModuleAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_MODULE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2025-01-06.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class VariableAssignmentIRInjectorStrategy {
public:
    void inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};


#endif //JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

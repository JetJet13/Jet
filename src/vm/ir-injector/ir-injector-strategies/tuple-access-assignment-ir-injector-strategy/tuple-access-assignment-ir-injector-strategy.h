//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_TUPLE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-tuple-access-assignment-statement-node.h"

class TupleAccessAssignmentIRInjectorStrategy {
public:
    void inject(IRTupleAccessAssignmentStatementNode* irTupleAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

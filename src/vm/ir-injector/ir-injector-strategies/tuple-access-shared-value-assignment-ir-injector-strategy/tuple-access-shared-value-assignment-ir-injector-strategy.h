//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-tuple-access-shared-value-assignment-statement-node.h"

class TupleAccessSharedValueAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRTupleAccessSharedValueAssignmentStatementNode> irTupleAccessSharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

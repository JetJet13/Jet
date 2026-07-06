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
    void inject(std::shared_ptr<IRTupleAccessAssignmentStatementNode> irTupleAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

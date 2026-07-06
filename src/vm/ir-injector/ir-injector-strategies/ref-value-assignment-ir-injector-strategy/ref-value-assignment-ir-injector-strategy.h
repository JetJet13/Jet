//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-ref-value-assignment-statement-node.h"

class RefValueAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRRefValueAssignmentStatementNode> irRefValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-ref-value-assignment-statement-node.h"

class ClassPropertyRefValueAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRClassPropertyRefValueAssignmentStatementNode> irClassPropertyRefValueAssignmentStatementNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

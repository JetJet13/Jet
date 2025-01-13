//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-assignment-statement-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "../../ir-injector.h"

class ClassPropertyAssignmentIRInjectorStrategy {
public:
    void inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

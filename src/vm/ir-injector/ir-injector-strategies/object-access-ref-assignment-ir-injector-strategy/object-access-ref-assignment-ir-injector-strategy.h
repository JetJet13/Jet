//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-ref-assignment-statement-node.h"

class ObjectAccessRefAssignmentIRInjectorStrategy {
public:
    void inject(IRObjectAccessRefAssignmentStatementNode* irObjectAccessRefAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

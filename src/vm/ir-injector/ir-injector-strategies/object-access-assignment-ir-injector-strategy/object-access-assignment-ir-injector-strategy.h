//
// Created by Johny Georges on 2025-08-30.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-node.h"

class ObjectAccessAssignmentIRInjectorStrategy {
public:
    void inject(IRObjectAccessAssignmentStatementNode* irObjectAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

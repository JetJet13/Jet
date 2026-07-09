//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-array-access-assignment-statement-node.h"

class ArrayAccessAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRArrayAccessAssignmentStatementNode> irArrayAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};


#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

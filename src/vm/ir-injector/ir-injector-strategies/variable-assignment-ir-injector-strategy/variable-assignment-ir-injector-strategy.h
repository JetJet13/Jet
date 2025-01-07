//
// Created by Johny Georges on 2025-01-06.
//

#ifndef JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"

class IRInjectorMap;

class VariableAssignmentIRInjectorStrategy {
public:
    void inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule, IRLookupTable* scope);
};


#endif //JETLANG_VARIABLE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

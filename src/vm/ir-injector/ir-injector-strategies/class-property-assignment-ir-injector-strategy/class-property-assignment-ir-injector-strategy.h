//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-assignment-statement-node.h"

class IRInjectorMap;

class ClassPropertyAssignmentIRInjectorStrategy {
public:
    void inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap *irInjectorMap, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

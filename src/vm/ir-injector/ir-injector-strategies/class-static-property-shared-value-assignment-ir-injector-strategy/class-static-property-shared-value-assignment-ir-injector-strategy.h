//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_CLASS_STATIC_PROPERTY_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_STATIC_PROPERTY_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-shared-value-assignment-statement-node.h"

class ClassStaticPropertySharedValueAssignmentIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRClassStaticPropertySharedValueAssignmentStatementNode> irClassStaticPropertySharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_CLASS_STATIC_PROPERTY_SHARED_VALUE_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

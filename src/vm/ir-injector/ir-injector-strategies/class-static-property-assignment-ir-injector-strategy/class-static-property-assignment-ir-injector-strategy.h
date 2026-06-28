//
// Created by Johny Georges on 2026-03-16.
//

#ifndef JETLANG_CLASS_STATIC_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_STATIC_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-assignment-statement-node.h"

class ClassStaticPropertyAssignmentIRInjectorStrategy {
public:
    void inject(IRClassStaticPropertyAssignmentStatementNode* irClassStaticPropertyAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_STATIC_PROPERTY_ASSIGNMENT_IR_INJECTOR_STRATEGY_H

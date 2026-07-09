//
// Created by Johny Georges on 2025-01-09.
//

#ifndef JETLANG_IF_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_IF_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"
#include "../../ir-injector.h"

class IfStatementIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRIfStatementNode> irIfStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};


#endif //JETLANG_IF_STATEMENT_IR_INJECTOR_STRATEGY_H

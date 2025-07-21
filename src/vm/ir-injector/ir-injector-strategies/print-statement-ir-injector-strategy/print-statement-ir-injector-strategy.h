//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_PRINT_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-print-statement-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../ir-injector.h"

class PrintStatementIRInjectorStrategy {
public:
    void inject(IRPrintStatementNode* irPrintStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_PRINT_STATEMENT_IR_INJECTOR_STRATEGY_H

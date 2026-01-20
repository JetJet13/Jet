//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_WHILE_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_WHILE_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"
#include "../../ir-injector.h"

class WhileStatementIRInjectorStrategy {
public:
    void inject(IRWhileStatementNode* irWhileStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_WHILE_STATEMENT_IR_INJECTOR_STRATEGY_H

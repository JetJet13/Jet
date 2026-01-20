//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-for-in-statement-node/ir-for-in-statement-node.h"
#include "../../ir-injector.h"

class ForInStatementIRInjectorStrategy {
public:
    void inject(IRForInStatementNode* irForInStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_FOR_IN_STATEMENT_IR_INJECTOR_STRATEGY_H

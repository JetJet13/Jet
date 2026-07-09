//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_IR_INJECTOR_STRATEGY_H
#define JETLANG_EXPRESSION_STATEMENT_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-expression-statement-node.h"
#include "../../ir-injector.h"

class ExpressionStatementIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRExpressionStatementNode> irExpressionStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_EXPRESSION_STATEMENT_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2025-07-25.
//

#ifndef JETLANG_VOID_IR_INJECTOR_STRATEGY_H
#define JETLANG_VOID_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"

class VoidIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) override;

};

#endif //JETLANG_VOID_IR_INJECTOR_STRATEGY_H

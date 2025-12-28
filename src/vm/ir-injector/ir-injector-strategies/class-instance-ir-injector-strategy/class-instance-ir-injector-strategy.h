//
// Created by Johny Georges on 2025-12-26.
//

#ifndef JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H
#define JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"


class ClassInstanceIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) override;
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

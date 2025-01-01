//
// Created by Johny Georges on 2025-01-01.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-new-class-instance-expression-node.h"
#include "../ir-injector-strategy.h"


class NewClassInstanceIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) override;
    llvm::Value* inject(IRNewClassInstanceExpressionNode* irNewClassInstanceExpressionNode, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

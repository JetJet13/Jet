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
#include "strategies/class-instance-ir-object-access-expression-injector-strategy/class-instance-ir-object-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-tuple-access-expression-injector-strategy/class-instance-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-array-access-expression-injector-strategy/class-instance-ir-array-access-expression-injector-strategy.h"
#include "strategies/class-instance-ir-dref-expression-injector-strategy/class-instance-ir-dref-expression-injector-strategy.h"
#include "strategies/class-instance-ir-this-expression-injector-strategy/class-instance-ir-this-expression-injector-strategy.h"


class ClassInstanceIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    ClassInstanceIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = ClassInstanceIRObjectAccessExpressionInjectorStrategy();
    ClassInstanceIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = ClassInstanceIRTupleAccessExpressionInjectorStrategy();
    ClassInstanceIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = ClassInstanceIRArrayAccessExpressionInjectorStrategy();
    ClassInstanceIRDrefExpressionInjectorStrategy _drefExpressionInjector = ClassInstanceIRDrefExpressionInjectorStrategy();
    ClassInstanceIRThisExpressionInjectorStrategy _thisExpressionInjector = ClassInstanceIRThisExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
    llvm::Value* inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_CLASS_INSTANCE_IR_INJECTOR_STRATEGY_H

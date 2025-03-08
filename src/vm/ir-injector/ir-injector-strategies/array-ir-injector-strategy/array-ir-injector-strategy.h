//
// Created by Johny Georges on 2024-08-13.
//

#ifndef JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-parameter-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "strategies/array-ir-array-expression-injector-strategy/array-ir-array-expression-injector-strategy.h"
#include "strategies/array-ir-object-access-expression-injector-strategy/array-ir-object-access-expression-injector-strategy.h"
#include "strategies/array-ir-array-access-expression-injector-strategy/array-ir-array-access-expression-injector-strategy.h"
#include "strategies/array-ir-tuple-access-expression-injector-strategy/array-ir-tuple-access-expression-injector-strategy.h"

class ArrayIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    ArrayIRArrayExpressionInjectorStrategy _arrayIRArrayExpressionInjectorStrategy = ArrayIRArrayExpressionInjectorStrategy();
    ArrayIRObjectAccessExpressionInjectorStrategy _arrayIRObjectAccessExpressionInjectorStrategy = ArrayIRObjectAccessExpressionInjectorStrategy();
    ArrayIRArrayAccessExpressionInjectorStrategy _arrayIRArrayAccessExpressionInjectorStrategy = ArrayIRArrayAccessExpressionInjectorStrategy();
    ArrayIRTupleAccessExpressionInjectorStrategy _arrayIRTupleAccessExpressionInjectorStrategy = ArrayIRTupleAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_ARRAY_IR_INJECTOR_STRATEGY_H

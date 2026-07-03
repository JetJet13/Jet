//
// Created by Johny Georges on 2024-08-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H
#define JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-struct-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/struct-ir-struct-expression-injector-strategy/struct-ir-struct-expression-injector-strategy.h"
#include "strategies/struct-ir-identifier-expression-injector-strategy/struct-ir-identifier-expression-injector-strategy.h"
#include "strategies/struct-ir-object-access-expression-injector-strategy/struct-ir-object-access-expression-injector-strategy.h"
#include "strategies/struct-ir-array-access-expression-injector-strategy/struct-ir-array-access-expression-injector-strategy.h"
#include "strategies/struct-ir-tuple-access-expression-injector-strategy/struct-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/struct-ir-class-property-access-expression-injector-strategy/struct-ir-class-property-access-expression-injector-strategy.h"
#include "strategies/struct-ir-dref-expression-injector-strategy/struct-ir-dref-expression-injector-strategy.h"

class StructIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    StructIRStructExpressionInjectorStrategy _structIRStructExpressionInjectorStrategy = StructIRStructExpressionInjectorStrategy();
    StructIRIdentifierExpressionInjectorStrategy _structIRIdentifierExpressionInjectorStrategy = StructIRIdentifierExpressionInjectorStrategy();
    StructIRObjectAccessExpressionInjectorStrategy _structIRObjectAccessExpressionInjectorStrategy = StructIRObjectAccessExpressionInjectorStrategy();
    StructIRArrayAccessExpressionInjectorStrategy _structIRArrayAccessExpressionInjectorStrategy = StructIRArrayAccessExpressionInjectorStrategy();
    StructIRTupleAccessExpressionInjectorStrategy _structIRTupleAccessExpressionInjectorStrategy = StructIRTupleAccessExpressionInjectorStrategy();
    StructIRClassPropertyAccessExpressionInjectorStrategy _structIRClassPropertyAccessExpressionInjectorStrategy = StructIRClassPropertyAccessExpressionInjectorStrategy();
    StructIRDrefExpressionInjectorStrategy _structIRDrefExpressionInjectorStrategy = StructIRDrefExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H

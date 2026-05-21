//
// Created by Johny Georges on 2025-02-18.
//

#ifndef JETLANG_ENUM_IR_INJECTOR_STRATEGY_H
#define JETLANG_ENUM_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "strategies/enum-ir-object-access-expression-strategy/enum-ir-object-access-expression-strategy.h"
#include "strategies/enum-ir-tuple-access-expression-strategy/enum-ir-tuple-access-expression-strategy.h"
#include "strategies/enum-ir-array-access-expression-strategy/enum-ir-array-access-expression-strategy.h"
#include "strategies/enum-ir-dref-expression-strategy/enum-ir-dref-expression-strategy.h"
#include "strategies/enum-ir-identifier-expression-strategy/enum-ir-identifier-expression-strategy.h"

class EnumIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    EnumIRIdentifierExpressionInjectorStrategy _enumIRIdentifierExpressionInjectorStrategy = EnumIRIdentifierExpressionInjectorStrategy();
    EnumIRDrefExpressionInjectorStrategy _enumIRDrefExpressionInjectorStrategy = EnumIRDrefExpressionInjectorStrategy();
    EnumIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = EnumIRArrayAccessExpressionInjectorStrategy();
    EnumIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = EnumIRObjectAccessExpressionInjectorStrategy();
    EnumIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = EnumIRTupleAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_ENUM_IR_INJECTOR_STRATEGY_H

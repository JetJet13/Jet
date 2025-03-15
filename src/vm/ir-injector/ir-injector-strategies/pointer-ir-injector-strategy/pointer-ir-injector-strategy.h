//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "strategies/pointer-ir-ref-expression-injector-strategy/pointer-ir-ref-expression-injector-strategy.h"

class PointerIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    PointerIRRefExpressionInjectorStrategy _pointerIRRefExpressionInjectorStrategy = PointerIRRefExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

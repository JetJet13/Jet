//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/pointer-ir-ref-expression-injector-strategy/pointer-ir-ref-expression-injector-strategy.h"
#include "strategies/pointer-ir-identifier-expression-injector-strategy/pointer-ir-identifier-expression-injector-strategy.h"

class PointerIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    PointerIRRefExpressionInjectorStrategy _pointerIRRefExpressionInjectorStrategy = PointerIRRefExpressionInjectorStrategy();
    PointerIRIdentifierExpressionInjectorStrategy _pointerIRIdentifierExpressionInjectorStrategy = PointerIRIdentifierExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/pointer-ir-identifier-expression-injector-strategy/pointer-ir-identifier-expression-injector-strategy.h"
#include "strategies/pointer-ir-share-expression-injector-strategy/pointer-ir-share-expression-injector-strategy.h"

class PointerIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    PointerIRShareExpressionInjectorStrategy _pointerIRShareExpressionInjectorStrategy = PointerIRShareExpressionInjectorStrategy();
    PointerIRIdentifierExpressionInjectorStrategy _pointerIRIdentifierExpressionInjectorStrategy = PointerIRIdentifierExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
};

#endif //JETLANG_POINTER_IR_INJECTOR_STRATEGY_H

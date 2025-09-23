//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_IR_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "strategies/ref-ir-ref-expression-injector-strategy/ref-ir-ref-expression-injector-strategy.h"
#include "strategies/ref-ir-identifier-expression-injector-strategy/ref-ir-identifier-expression-injector-strategy.h"
#include "strategies/ref-ir-sref-expression-injector-strategy/ref-ir-sref-expression-injector-strategy.h"
#include "strategies/ref-ir-object-access-expression-injector-strategy/ref-ir-object-access-expression-injector-strategy.h"

class RefIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    RefIRRefExpressionInjectorStrategy _refIRRefExpressionInjectorStrategy = RefIRRefExpressionInjectorStrategy();
    RefIRIdentifierExpressionInjectorStrategy _refIRIdentifierExpressionInjectorStrategy = RefIRIdentifierExpressionInjectorStrategy();
    RefIRSrefExpressionInjectorStrategy _refIRSrefExpressionInjectorStrategy = RefIRSrefExpressionInjectorStrategy();
    RefIRObjectAccessExpressionInjectorStrategy _refIRObjectAccessExpressionInjectorStrategy = RefIRObjectAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_REF_IR_INJECTOR_STRATEGY_H

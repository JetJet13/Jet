//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_IR_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/ref-ir-ref-expression-injector-strategy/ref-ir-ref-expression-injector-strategy.h"
#include "strategies/ref-ir-identifier-expression-injector-strategy/ref-ir-identifier-expression-injector-strategy.h"
#include "strategies/ref-ir-object-access-expression-injector-strategy/ref-ir-object-access-expression-injector-strategy.h"
#include "strategies/ref-ir-array-access-expression-injector-strategy/ref-ir-array-access-expression-injector-strategy.h"
#include "strategies/ref-ir-function-invocation-expression-injector-strategy/ref-ir-function-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-class-static-method-invocation-expression-injector-strategy/ref-ir-class-static-method-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-object-access-invocation-expression-injector-strategy/ref-ir-object-access-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-array-access-invocation-expression-injector-strategy/ref-ir-array-access-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-tuple-access-invocation-expression-injector-strategy/ref-ir-tuple-access-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-class-method-invocation-expression-injector-strategy/ref-ir-class-method-invocation-expression-injector-strategy.h"
#include "strategies/ref-ir-class-property-access-expression-injector-strategy/ref-ir-class-property-access-expression-injector-strategy.h"
#include "strategies/ref-ir-tuple-access-expression-injector-strategy/ref-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/ref-ir-module-access-expression-injector-strategy/ref-ir-module-access-expression-injector-strategy.h"

class RefIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    RefIRRefExpressionInjectorStrategy _refIRRefExpressionInjectorStrategy = RefIRRefExpressionInjectorStrategy();
    RefIRIdentifierExpressionInjectorStrategy _refIRIdentifierExpressionInjectorStrategy = RefIRIdentifierExpressionInjectorStrategy();
    RefIRFunctionInvocationExpressionInjectorStrategy _refIRFunctionInvocationExpressionInjectorStrategy = RefIRFunctionInvocationExpressionInjectorStrategy();
    RefIRObjectAccessInvocationExpressionInjectorStrategy _refIRObjectAccessInvocationExpressionInjectorStrategy = RefIRObjectAccessInvocationExpressionInjectorStrategy();
    RefIRArrayAccessInvocationExpressionInjectorStrategy _refIRArrayAccessInvocationExpressionInjectorStrategy = RefIRArrayAccessInvocationExpressionInjectorStrategy();
    RefIRTupleAccessInvocationExpressionInjectorStrategy _refIRTupleAccessInvocationExpressionInjectorStrategy = RefIRTupleAccessInvocationExpressionInjectorStrategy();
    RefIRClassMethodInvocationExpressionInjectorStrategy _refIRClassMethodInvocationExpressionInjectorStrategy = RefIRClassMethodInvocationExpressionInjectorStrategy();
    RefIRClassStaticMethodInvocationExpressionInjectorStrategy _refIRClassStaticMethodInvocationExpressionInjectorStrategy = RefIRClassStaticMethodInvocationExpressionInjectorStrategy();
    RefIRClassPropertyAccessExpressionInjectorStrategy _refIRClassPropertyAccessExpressionInjectorStrategy = RefIRClassPropertyAccessExpressionInjectorStrategy();
    RefIRObjectAccessExpressionInjectorStrategy _refIRObjectAccessExpressionInjectorStrategy = RefIRObjectAccessExpressionInjectorStrategy();
    RefIRArrayAccessExpressionInjectorStrategy _refIRArrayAccessExpressionInjectorStrategy = RefIRArrayAccessExpressionInjectorStrategy();
    RefIRTupleAccessExpressionInjectorStrategy _refIRTupleAccessExpressionInjectorStrategy = RefIRTupleAccessExpressionInjectorStrategy();
    RefIRModuleAccessExpressionInjectorStrategy _refIRModuleAccessExpressionInjectorStrategy = RefIRModuleAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
};

#endif //JETLANG_REF_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_SHARED_PTR_IR_INJECTOR_STRATEGY_H
#define JETLANG_SHARED_PTR_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/shared-ptr-ir-share-expression-injector-strategy/shared-ptr-ir-share-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-identifier-expression-injector-strategy/shared-ptr-ir-identifier-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-object-access-expression-injector-strategy/shared-ptr-ir-object-access-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-array-access-expression-injector-strategy/shared-ptr-ir-array-access-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-function-invocation-expression-injector-strategy/shared-ptr-ir-function-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-class-static-method-invocation-expression-injector-strategy/shared-ptr-ir-class-static-method-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-object-access-invocation-expression-injector-strategy/shared-ptr-ir-object-access-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-array-access-invocation-expression-injector-strategy/shared-ptr-ir-array-access-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-tuple-access-invocation-expression-injector-strategy/shared-ptr-ir-tuple-access-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-class-method-invocation-expression-injector-strategy/shared-ptr-ir-class-method-invocation-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-class-property-access-expression-injector-strategy/shared-ptr-ir-class-property-access-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-tuple-access-expression-injector-strategy/shared-ptr-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/shared-ptr-ir-module-access-expression-injector-strategy/shared-ptr-ir-module-access-expression-injector-strategy.h"

class SharedPtrIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    SharedPtrIRShareExpressionInjectorStrategy _sharedPtrIRShareExpressionInjectorStrategy = SharedPtrIRShareExpressionInjectorStrategy();
    SharedPtrIRIdentifierExpressionInjectorStrategy _sharedPtrIRIdentifierExpressionInjectorStrategy = SharedPtrIRIdentifierExpressionInjectorStrategy();
    SharedPtrIRFunctionInvocationExpressionInjectorStrategy _sharedPtrIRFunctionInvocationExpressionInjectorStrategy = SharedPtrIRFunctionInvocationExpressionInjectorStrategy();
    SharedPtrIRObjectAccessInvocationExpressionInjectorStrategy _sharedPtrIRObjectAccessInvocationExpressionInjectorStrategy = SharedPtrIRObjectAccessInvocationExpressionInjectorStrategy();
    SharedPtrIRArrayAccessInvocationExpressionInjectorStrategy _sharedPtrIRArrayAccessInvocationExpressionInjectorStrategy = SharedPtrIRArrayAccessInvocationExpressionInjectorStrategy();
    SharedPtrIRTupleAccessInvocationExpressionInjectorStrategy _sharedPtrIRTupleAccessInvocationExpressionInjectorStrategy = SharedPtrIRTupleAccessInvocationExpressionInjectorStrategy();
    SharedPtrIRClassMethodInvocationExpressionInjectorStrategy _sharedPtrIRClassMethodInvocationExpressionInjectorStrategy = SharedPtrIRClassMethodInvocationExpressionInjectorStrategy();
    SharedPtrIRClassStaticMethodInvocationExpressionInjectorStrategy _sharedPtrIRClassStaticMethodInvocationExpressionInjectorStrategy = SharedPtrIRClassStaticMethodInvocationExpressionInjectorStrategy();
    SharedPtrIRClassPropertyAccessExpressionInjectorStrategy _sharedPtrIRClassPropertyAccessExpressionInjectorStrategy = SharedPtrIRClassPropertyAccessExpressionInjectorStrategy();
    SharedPtrIRObjectAccessExpressionInjectorStrategy _sharedPtrIRObjectAccessExpressionInjectorStrategy = SharedPtrIRObjectAccessExpressionInjectorStrategy();
    SharedPtrIRArrayAccessExpressionInjectorStrategy _sharedPtrIRArrayAccessExpressionInjectorStrategy = SharedPtrIRArrayAccessExpressionInjectorStrategy();
    SharedPtrIRTupleAccessExpressionInjectorStrategy _sharedPtrIRTupleAccessExpressionInjectorStrategy = SharedPtrIRTupleAccessExpressionInjectorStrategy();
    SharedPtrIRModuleAccessExpressionInjectorStrategy _sharedPtrIRModuleAccessExpressionInjectorStrategy = SharedPtrIRModuleAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) override;
};

#endif //JETLANG_SHARED_PTR_IR_INJECTOR_STRATEGY_H

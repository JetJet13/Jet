//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-block-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "strategies/lambda-ir-object-access-expression-injector-strategy/lambda-ir-object-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-tuple-access-expression-injector-strategy/lambda-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-array-access-expression-injector-strategy/lambda-ir-array-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-identifier-expression-injector-strategy/lambda-ir-identifier-expression-injector-strategy.h"
#include "strategies/lambda-ir-module-access-expression-injector-strategy/lambda-ir-module-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-lambda-with-block-expression-injector-strategy/lambda-ir-lambda-with-block-expression-injector-strategy.h"
#include "strategies/lambda-ir-lambda-with-fat-arrow-expression-injector-strategy/lambda-ir-lambda-with-fat-arrow-expression-injector-strategy.h"
#include "strategies/lambda-class-static-method-invocation-expression-injector-strategy/lambda-class-static-method-invocation-expression-injector-strategy.h"
#include "strategies/lambda-ir-object-access-invocation-expression-injector-strategy/lambda-ir-object-access-invocation-expression-injector-strategy.h"
#include "strategies/lambda-ir-array-access-invocation-expression-injector-strategy/lambda-ir-array-access-invocation-expression-injector-strategy.h"
#include "strategies/lambda-ir-function-invocation-expression-injector-strategy/lambda-ir-function-invocation-expression-injector-strategy.h"
#include "strategies/lambda-ir-tuple-access-invocation-expression-injector-strategy/lambda-ir-tuple-access-invocation-expression-injector-strategy.h"

class LambdaIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    LambdaIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = LambdaIRObjectAccessExpressionInjectorStrategy();
    LambdaIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = LambdaIRTupleAccessExpressionInjectorStrategy();
    LambdaIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = LambdaIRArrayAccessExpressionInjectorStrategy();
    LambdaIRIdentifierExpressionInjectorStrategy _identifierExpressionInjector = LambdaIRIdentifierExpressionInjectorStrategy();
    LambdaIRModuleAccessExpressionInjectorStrategy _moduleAccessExpressionInjector = LambdaIRModuleAccessExpressionInjectorStrategy();
    LambdaIRLambdaWithBlockExpressionInjectorStrategy _lambdaWithBlockExpressionInjector = LambdaIRLambdaWithBlockExpressionInjectorStrategy();
    LambdaIRLambdaWithFatArrowExpressionInjectorStrategy _lambdaWithFatArrowExpressionInjector = LambdaIRLambdaWithFatArrowExpressionInjectorStrategy();
    LambdaIRClassStaticMethodInvocationExpressionInjectorStrategy _classStaticMethodInvocationExpressionInjector = LambdaIRClassStaticMethodInvocationExpressionInjectorStrategy();
    LambdaIRObjectAccessInvocationExpressionInjectorStrategy _objectAccessInvocationExpressionInjector = LambdaIRObjectAccessInvocationExpressionInjectorStrategy();
    LambdaIRTupleAccessInvocationExpressionInjectorStrategy _tupleAccessInvocationExpressionInjector = LambdaIRTupleAccessInvocationExpressionInjectorStrategy();
    LambdaIRArrayAccessInvocationExpressionInjectorStrategy _arrayAccessInvocationExpressionInjector = LambdaIRArrayAccessInvocationExpressionInjectorStrategy();
    LambdaIRFunctionInvocationExpressionInjectorStrategy _functionInvocationExpressionInjector = LambdaIRFunctionInvocationExpressionInjectorStrategy();
public:
    llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};


#endif //JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

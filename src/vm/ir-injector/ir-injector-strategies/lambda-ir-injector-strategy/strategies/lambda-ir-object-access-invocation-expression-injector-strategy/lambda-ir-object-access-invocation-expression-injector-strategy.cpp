//
// Created by Johny Georges on 2026-06-02.
//

#include "lambda-ir-object-access-invocation-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/lambda-ir-injector-helper/lambda-ir-injector-helper.h"

llvm::Value* LambdaIRObjectAccessInvocationExpressionInjectorStrategy::inject(IRObjectAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, irOperation);
    LambdaIRInjectorHelper::incrementRefCountForInvocationExpression(functionResult, irExpression->getIRType(), irBlock,
                                                                     irOperation, irModule);
    return functionResult;
}
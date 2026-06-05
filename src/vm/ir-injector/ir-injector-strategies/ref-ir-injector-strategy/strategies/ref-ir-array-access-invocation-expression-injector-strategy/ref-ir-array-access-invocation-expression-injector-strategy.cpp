//
// Created by Johny Georges on 2026-06-02.
//

#include "ref-ir-array-access-invocation-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-injector-helpers/ref-ir-injector-helper/ref-ir-injector-helper.h"

llvm::Value* RefIRArrayAccessInvocationExpressionInjectorStrategy::inject(IRArrayAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, irOperation);
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    RefIRInjectorHelper::incrementRefCountForInvocationExpression(functionResult, irRefType, irBlock, irOperation,
                                                                  irModule);
    return RefIRInjectorHelper::inject(functionResult, irRefType, irBlock, irOperation);
}
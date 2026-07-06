//
// Created by Johny Georges on 2026-06-13.
//

#include "ref-ir-class-method-invocation-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/ref-ir-injector-helper/ref-ir-injector-helper.h"

llvm::Value* RefIRClassMethodInvocationExpressionInjectorStrategy::inject(std::shared_ptr<IRClassMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_POINTER_OP));
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    RefIRInjectorHelper::incrementRefCountForInvocationExpression(functionResult, irRefType, irBlock, irOperation, irModule);
    return RefIRInjectorHelper::injectForInvocationExpression(functionResult, irRefType, irBlock, irOperation);
}
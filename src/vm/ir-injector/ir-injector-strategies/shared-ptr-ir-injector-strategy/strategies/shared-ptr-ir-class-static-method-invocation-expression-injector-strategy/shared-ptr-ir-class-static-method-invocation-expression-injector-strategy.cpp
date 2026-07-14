//
// Created by Johny Georges on 2026-06-02.
//

#include "shared-ptr-ir-class-static-method-invocation-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../../../ir-type/ir-shared-ptr-type.h"
#include "../../../ir-injector-helpers/shared-ptr-ir-injector-helper/shared-ptr-ir-injector-helper.h"

llvm::Value* SharedPtrIRClassStaticMethodInvocationExpressionInjectorStrategy::inject(std::shared_ptr<IRClassStaticMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getIRType()->getSourceType());
    SharedPtrIRInjectorHelper::incrementSharedPtrCountForInvocationExpression(functionResult, irSharedPtrType, irBlock, irOperation, irModule);
    return SharedPtrIRInjectorHelper::injectForInvocationExpression(functionResult, irSharedPtrType, irBlock, irOperation);
}
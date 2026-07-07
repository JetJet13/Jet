//
// Created by Johny Georges on 2026-06-02.
//

#include "ref-ir-tuple-access-invocation-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-injector-helpers/ref-ir-injector-helper/ref-ir-injector-helper.h"

llvm::Value* RefIRTupleAccessInvocationExpressionInjectorStrategy::inject(std::shared_ptr<IRTupleAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    RefIRInjectorHelper::incrementRefCountForInvocationExpression(functionResult, irRefType, irBlock, irOperation, irModule);
    return RefIRInjectorHelper::injectForInvocationExpression(functionResult, irRefType, irBlock, irOperation);
}
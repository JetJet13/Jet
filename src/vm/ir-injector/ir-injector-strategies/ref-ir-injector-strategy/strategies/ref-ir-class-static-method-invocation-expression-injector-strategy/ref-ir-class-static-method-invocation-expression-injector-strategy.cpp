//
// Created by Johny Georges on 2026-06-02.
//

#include "ref-ir-class-static-method-invocation-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/ref-ir-injector-helper/ref-ir-injector-helper.h"

llvm::Value* RefIRClassStaticMethodInvocationExpressionInjectorStrategy::inject(IRClassStaticMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto functionResult = FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_POINTER_OP));
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    RefIRInjectorHelper::incrementRefCountForInvocationExpression(functionResult, irRefType, irBlock, irOperation,
                                                                  irModule);
    return RefIRInjectorHelper::inject(functionResult, irRefType, irBlock, irOperation);
}
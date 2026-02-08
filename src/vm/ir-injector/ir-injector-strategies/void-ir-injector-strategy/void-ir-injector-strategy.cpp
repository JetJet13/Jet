//
// Created by Johny Georges on 2025-07-25.
//

#include "void-ir-injector-strategy.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

llvm::Value* VoidIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRObjectAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRTupleAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("VoidIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
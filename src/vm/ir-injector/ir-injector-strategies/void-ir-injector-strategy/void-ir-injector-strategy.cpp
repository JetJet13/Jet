//
// Created by Johny Georges on 2025-07-25.
//

#include "void-ir-injector-strategy.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

llvm::Value* VoidIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRFunctionInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRObjectAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRTupleAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRArrayAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRArrayPrototypeInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_STRING_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRStringPrototypeInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRArrayAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_SHARED_PTR_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRSharedPtrPrototypeInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("VoidIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
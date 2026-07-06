//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector-strategy.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"

llvm::Value* TupleIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->_tupleIRTupleExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRTupleExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_tupleIRIdentifierExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRIdentifierExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_tupleIRDrefExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRDrefExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRObjectAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRArrayAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRTupleAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRClassPropertyAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRClassPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRFunctionInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_MODULE_ACCESS_EXPRESSION_NODE)) {
        return ModuleAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("TupleIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
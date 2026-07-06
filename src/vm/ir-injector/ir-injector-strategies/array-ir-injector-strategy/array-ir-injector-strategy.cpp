//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* ArrayIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector *irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_ARRAY_EXPRESSION_NODE)) {
        return this->_arrayIRArrayExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRArrayExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayIRObjectAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRObjectAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayIRArrayAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayIRTupleAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_arrayIRDrefExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRDrefExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_arrayIRIdentifierExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRIdentifierExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CONCAT_EXPRESSION_NODE)) {
        return this->_arrayIRConcatExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRConcatExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRFunctionInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject(std::dynamic_pointer_cast<IRArrayPrototypeInvocationExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_MODULE_ACCESS_EXPRESSION_NODE)) {
        return ModuleAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("ArrayIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-injector-strategy.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* RefIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->is(IR_REF_EXPRESSION_NODE)) {
        return this->_refIRRefExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRRefExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_refIRIdentifierExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRIdentifierExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRObjectAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRTupleAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRArrayAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_MODULE_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRModuleAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRFunctionInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRFunctionInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRObjectAccessInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRObjectAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRArrayAccessInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRArrayAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRClassStaticMethodInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRClassStaticMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRClassMethodInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRClassMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_refIRTupleAccessInvocationExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRTupleAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRClassPropertyAccessExpressionInjectorStrategy.inject(std::dynamic_pointer_cast<IRClassPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject(std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irExpression), irBlock, irInjector, irModule, scope, irOperation);
    }
    Logger::log(irExpression->toString());
    throw std::logic_error("RefIRInjectorStrategy - invalid ir expression with ref type");
}
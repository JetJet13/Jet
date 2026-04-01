//
// Created by Johny Georges on 2024-08-14.
//

#include "literal-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"

llvm::Value* LiteralIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_LITERAL_EXPRESSION_NODE)) {
        return this->_literalExpressionInjector.inject((IRLiteralExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_identifierExpressionInjector.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_objectAccessExpressionInjector.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_binaryArithmeticExpressionInjector.inject((IRBinaryArithmeticExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_BINARY_COMPARISON_EXPRESSION_NODE)) {
        return this->_binaryComparisonExpressionInjector.inject((IRBinaryComparisonExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_UNARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_unaryArithmeticExpressionInjector.inject((IRUnaryArithmeticExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_UNARY_NEGATE_EXPRESSION_NODE)) {
        return this->_unaryNegateExpressionInjector.inject((IRUnaryNegateExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LOGICAL_EXPRESSION_NODE)) {
        return this->_logicalExpressionInjector.inject((IRLogicalExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayAccessExpressionInjector.inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleAccessExpressionInjector.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_literalIRDrefExpressionInjectorStrategy.inject((IRDrefExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassStaticPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRClassMethodInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRClassStaticMethodInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_STRING_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRStringPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRRefPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRTupleAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRObjectAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_MODULE_ACCESS_EXPRESSION_NODE)) {
        return ModuleAccessIRInjectorHelper::inject((IRModuleAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("LiteralIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
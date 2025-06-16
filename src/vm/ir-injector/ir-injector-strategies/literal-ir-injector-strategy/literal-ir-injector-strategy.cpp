//
// Created by Johny Georges on 2024-08-14.
//

#include "literal-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-type/ir-array-pointer-type.h"

llvm::Value* LiteralIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_LITERAL_EXPRESSION_NODE)) {
        return irExpression->getValue();
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_identifierExpressionInjector.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_objectAccessExpressionInjector.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_binaryArithmeticExpressionInjector.inject((IRBinaryArithmeticExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_BINARY_COMPARISON_EXPRESSION_NODE)) {
        return this->_binaryComparisonExpressionInjector.inject((IRBinaryComparisonExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_UNARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->_unaryArithmeticExpressionInjector.inject((IRUnaryArithmeticExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_UNARY_NEGATE_EXPRESSION_NODE)) {
        return this->_unaryNegateExpressionInjector.inject((IRUnaryNegateExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LOGICAL_EXPRESSION_NODE)) {
        return this->_logicalExpressionInjector.inject((IRLogicalExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayAccessExpressionInjector.inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleAccessExpressionInjector.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_literalIRDrefExpressionInjectorStrategy.inject((IRDrefExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRClassMethodInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    }
    throw std::logic_error("LiteralIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector-strategy.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* TupleIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->_tupleIRTupleExpressionInjectorStrategy.inject((IRTupleExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_tupleIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRTupleAccessExpressionInjectorStrategy.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleIRClassPropertyAccessExpressionInjectorStrategy.inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    }
    throw std::logic_error("TupleIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
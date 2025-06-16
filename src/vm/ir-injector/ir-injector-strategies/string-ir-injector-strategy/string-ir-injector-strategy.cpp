//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* StringIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->_stringIRStringLiteralExpressionInjectorStrategy.inject((IRStringLiteralExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_stringIRObjectAccessExpressionInjectorStrategy.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_stringIRArrayAccessExpressionInjectorStrategy.inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_stringIRTupleAccessExpressionInjectorStrategy.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_stringIRDrefExpressionInjectorStrategy.inject((IRDrefExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_stringIRClassPropertyAccessExpressionInjectorStrategy.inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_stringIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CONCAT_EXPRESSION_NODE)) {
        return this->_stringIRConcatExpressionInjectorStrategy.inject((IRConcatExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRArrayPrototypeInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope);
    }
    throw std::logic_error("StringIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

//
// Created by Johny Georges on 2024-12-05.
//

#include "lambda-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-type/ir-captured-variable-type.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"

llvm::Value* LambdaIRInjectorStrategy::inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_identifierExpressionInjector.inject(std::dynamic_pointer_cast<IRIdentifierExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE)) {
        return this->_lambdaWithBlockExpressionInjector.inject(std::dynamic_pointer_cast<IRLambdaWithBlockExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE)) {
        return this->_lambdaWithFatArrowExpressionInjector.inject(std::dynamic_pointer_cast<IRLambdaWithFatArrowExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->_functionInvocationExpressionInjector.inject(std::dynamic_pointer_cast<IRFunctionInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->_classStaticMethodInvocationExpressionInjector.inject(std::dynamic_pointer_cast<IRClassStaticMethodInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_objectAccessInvocationExpressionInjector.inject(std::dynamic_pointer_cast<IRObjectAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_arrayAccessInvocationExpressionInjector.inject(std::dynamic_pointer_cast<IRArrayAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return this->_tupleAccessInvocationExpressionInjector.inject(std::dynamic_pointer_cast<IRTupleAccessInvocationExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_objectAccessExpressionInjector.inject(std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_tupleAccessExpressionInjector.inject(std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_arrayAccessExpressionInjector.inject(std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_MODULE_ACCESS_EXPRESSION_NODE)) {
        return this->_moduleAccessExpressionInjector.inject(std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irExpression), irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("LambdaIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
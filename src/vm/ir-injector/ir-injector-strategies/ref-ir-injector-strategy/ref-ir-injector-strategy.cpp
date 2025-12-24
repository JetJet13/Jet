//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-injector-strategy.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"

llvm::Value* RefIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_REF_EXPRESSION_NODE)) {
        return this->_refIRRefExpressionInjectorStrategy.inject((IRRefExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_refIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_SREF_EXPRESSION_NODE)) {
        return this->_refIRSrefExpressionInjectorStrategy.inject((IRSrefExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_refIRObjectAccessExpressionInjectorStrategy.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRObjectAccessInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("RefIRInjectorStrategy - invalid ir expression with ref type");
}
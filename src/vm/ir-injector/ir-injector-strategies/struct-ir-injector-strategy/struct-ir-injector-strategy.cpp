//
// Created by Johny Georges on 2024-08-14.
//

#include "struct-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* StructIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_STRUCT_EXPRESSION_NODE)) {
        return this->_structIRStructExpressionInjectorStrategy.inject((IRStructExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_structIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->_structIRObjectAccessExpressionInjectorStrategy.inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_structIRArrayAccessExpressionInjectorStrategy.inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->_structIRTupleAccessExpressionInjectorStrategy.inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->_structIRClassPropertyAccessExpressionInjectorStrategy.inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_DREF_EXPRESSION_NODE)) {
        return this->_structIRDrefExpressionInjectorStrategy.inject((IRDrefExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
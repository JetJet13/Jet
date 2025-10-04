//
// Created by Johny Georges on 2025-07-25.
//

#include "void-ir-injector-strategy.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

llvm::Value* VoidIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("VoidIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* VoidIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}
//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-lambda-with-block-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../../../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-injector-helpers/lambda-ir-injector-helper/lambda-ir-injector-helper.h"

llvm::Value* LambdaIRLambdaWithBlockExpressionInjectorStrategy::inject(std::shared_ptr<IRLambdaWithBlockExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto lambdaScope = irExpression->getBlock()->getScope();

    auto lambdaScopeParameter = irExpression->getParameters()->getLambdaScopeParameter();
    if (lambdaScopeParameter) {
        InstructionIRInjectorHelper::inject(lambdaScopeParameter.value()->getAllocation(), irExpression->getBlock());
    }
    irInjector->inject(irBlock, irExpression->getBlock(), irModule);
    if (irExpression->getFunctionValue()->getReturnType()->isVoidTy()) {
        irExpression->getBlock()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(irExpression->getBlock(), irInjector, irModule, lambdaScope);
    FreeIRInjectorHelper::freeFunctionParameters(irExpression->getBlock(), irExpression->getParameters(), irInjector, irModule, lambdaScope);
    DebugIRInjectorHelper::injectFunctionEnterLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irExpression->getBlock(), irExpression->getFunctionValue()->getName().str(), irInjector, irModule);
    auto value = LambdaIRInjectorHelper::injectDetails(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    if (irOperation->isOperandPointer()) {
        return irExpression->getAllocation()->getValue();
    }
    return value;
}
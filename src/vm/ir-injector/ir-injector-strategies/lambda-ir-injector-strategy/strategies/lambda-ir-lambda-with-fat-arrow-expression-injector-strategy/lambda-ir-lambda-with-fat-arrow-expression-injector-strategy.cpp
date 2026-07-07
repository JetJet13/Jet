//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-lambda-with-fat-arrow-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../../../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-injector-helpers/lambda-ir-injector-helper/lambda-ir-injector-helper.h"

llvm::Value* LambdaIRLambdaWithFatArrowExpressionInjectorStrategy::inject(std::shared_ptr<IRLambdaWithFatArrowExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto lambdaScope = irExpression->getBlock()->getScope();
    auto lambdaScopeParameter = irExpression->getParameters()->getLambdaScopeParameter();
    if (lambdaScopeParameter) {
        InstructionIRInjectorHelper::inject(lambdaScopeParameter.value()->getAllocation(), irExpression->getBlock());
    }
    irInjector->inject(irBlock, irExpression->getBlock(), irModule);
    auto irReturnExpressionValue = irInjector->inject(irExpression->getBlock(), irExpression->getReturnExpression(), std::make_shared<IROperation>(IR_FUNCTION_RETURN_OP), irModule, lambdaScope);
    irExpression->getBlock()->getBuilder()->get()->CreateRet(irReturnExpressionValue);
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
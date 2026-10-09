// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-lambda-with-fat-arrow-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../../../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-injector-helpers/lambda-ir-injector-helper/lambda-ir-injector-helper.h"

llvm::Value* LambdaIRLambdaWithFatArrowExpressionInjectorStrategy::inject(std::shared_ptr<IRLambdaWithFatArrowExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
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
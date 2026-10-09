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
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRClassMethodInvocationExpressionNode> ClassMethodInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTClassMethodInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                argument,
                i,
                scope,
                irContext,
                std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                node->getName()->getMethodTypeSignature()
            )
        );
    }

    auto irFunctionType = std::dynamic_pointer_cast<IRFunctionType>(irGenerator->generateTypeFor(node->getName()->getTypeSignature(), scope, irContext));
    auto irReturnType = irGenerator->generateTypeFor(node->getName()->getMethodTypeSignature()->getReturnType(), scope, irContext);
    auto methodId = FunctionIdGenerator::generateFor(node->getName()->getId(), node->getArguments()->getArgumentListTypeSignature()->toDetailString());
    auto function = irContext->getModule()->getFunction(methodId);
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType, &arguments);

    // for class scope argument
    argList.push_back(irGenerator->generateConstantPointer());

    auto callInstruction = llvm::CallInst::Create(function->getFunctionType(), function, argList);
    return std::make_shared<IRClassMethodInvocationExpressionNode>(node, function, callInstruction, irFunctionType, arguments, irReturnType, scope->getClassScope().value());
}
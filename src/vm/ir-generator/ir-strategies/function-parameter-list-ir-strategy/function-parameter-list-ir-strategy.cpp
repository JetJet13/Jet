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
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-type/ir-invocable-type.h"

std::shared_ptr<IRFunctionParameterListNode> FunctionParameterListIRStrategy::generate(std::shared_ptr<ASTFunctionParameterListNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, llvm::Function* irFunction) {
    auto functionParameters = std::vector<std::shared_ptr<IRFunctionParameterNode>>();
    for (uint64_t i = 0; i < node->getParameters().size(); ++i) {
        auto parameter = node->getParameters()[i];
        auto parameterType = irGenerator->generateParameterType(parameter->getParameterTypeSignature(), scope, irContext);
        auto argument = new llvm::Argument(parameterType->getType(), parameterType->getName(), irFunction, i);
        auto allocation = irGenerator->generateFunctionParameterAllocation(parameter, parameterType, irContext);
        scope->insert(parameterType->getName(), allocation);
        auto irArc = std::optional<std::shared_ptr<IRInstructionNode>>();
        if (parameterType->getIRType()->requiresArc()) {
            irArc = irGenerator->generateArcAllocation(irContext, parameterType->getIRType(), irFunction->getArg(i), parameter->getCaptureCount());
            scope->insertArc(parameter->getIdentifier()->getId(), irArc.value());
        } else if (parameter->isCaptured()) {
            irArc = irGenerator->generateArcAllocation(irContext, parameter->getCaptureCount());
            scope->insertArc(parameter->getIdentifier()->getId(), irArc.value());
        }

        functionParameters.push_back(
            std::make_shared<IRFunctionParameterNode>(argument, parameterType, allocation, parameter, irArc)
        );

    }
    return std::make_shared<IRFunctionParameterListNode>(node, functionParameters);
}
//
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-type/ir-invocable-type.h"

std::shared_ptr<IRFunctionParameterListNode> FunctionParameterListIRStrategy::generate(std::shared_ptr<ASTFunctionParameterListNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, llvm::Function* irFunction) {
    auto functionParameters = std::vector<std::shared_ptr<IRFunctionParameterNode>>();
    for (unsigned long i = 0; i < node->getParameters().size(); ++i) {
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
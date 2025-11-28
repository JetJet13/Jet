//
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-type/ir-function-parameter-type.h"

IRFunctionParameterListNode* FunctionParameterListIRStrategy::generate(ASTFunctionParameterListNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, llvm::Function* irFunction) {
    auto functionParameters = std::vector<IRFunctionParameterNode*>();
    for (int i = 0; i < node->getParameters().size(); ++i) {
        auto parameter = node->getParameters()[i];
        auto parameterType = irGenerator->generateParameterType(parameter->getTypeSignature(), scope, irContext);
        auto argument = new llvm::Argument(parameterType->getType(), parameterType->getName(), irFunction, i);
        functionParameters.push_back(
            new IRFunctionParameterNode(argument, parameterType, parameter)
        );
    }
    return new IRFunctionParameterListNode(node, functionParameters);
}
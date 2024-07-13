//
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"

IRFunctionParameterListNode* FunctionParameterListIRStrategy::generate(ASTFunctionParameterListNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, llvm::Function* irFunction) {
    auto functionParameters = std::vector<IRFunctionParameterNode*>();
    for (int i = 0; i < node->getParameters().size(); ++i) {
        auto parameter = node->getParameters()[i];
        auto parameterType = irGenerator->generateParameterType(parameter->getTypeSignature());
        auto argument = new llvm::Argument(parameterType->getType(), parameterType->getName(), irFunction, i);
        functionParameters.push_back(
            new IRFunctionParameterNode(parameter, argument, parameterType)
        );
    }
    return new IRFunctionParameterListNode(node, functionParameters);
}
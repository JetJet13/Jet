//
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"

IRFunctionParameterListNode* FunctionParameterListIRStrategy::generate(ASTFunctionParameterListNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionParameters = std::vector<llvm::Argument*>();
    for (int i = 0; i < node->getParameters().size(); ++i) {
        auto parameter = node->getParameters()[i];
        auto functionParameter = irGenerator->generateParameterType(parameter->getTypeSignature());
        functionParameters.push_back(
            new llvm::Argument(functionParameter->getType(), functionParameter->getName(), nullptr, i)
        );
    }
    return new IRFunctionParameterListNode(node, functionParameters);
}
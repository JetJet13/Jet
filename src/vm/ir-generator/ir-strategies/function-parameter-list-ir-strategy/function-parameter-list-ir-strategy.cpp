//
// Created by Johny Georges on 2024-07-09.
//

#include "function-parameter-list-ir-strategy.h"

IRFunctionParameterListNode* FunctionParameterListIRStrategy::generate(ASTFunctionParameterListNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionParameters = std::vector<llvm::Argument*>();
}
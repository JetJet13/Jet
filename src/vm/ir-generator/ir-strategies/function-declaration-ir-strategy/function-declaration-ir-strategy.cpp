//
// Created by Johny Georges on 2024-07-08.
//

#include "function-declaration-ir-strategy.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

IRFunctionDeclarationNode* FunctionDeclarationIRStrategy::generate(ASTFunctionDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule);
    auto functionType = llvm::cast<llvm::FunctionType>(irGenerator->generateTypeFor(node->getTypeSignature())->getType());
    auto functionBlock = irGenerator->generateBasicBlock();
    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(
            irGenerator->generateFor((ASTDeclarationNode*)statement, scope, irModule)
        );
    }
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::PrivateLinkage, node->getId(), irModule->getModule());
    return new IRFunctionDeclarationNode(node, irFunction, functionParameterList, functionBlock);
}
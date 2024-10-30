//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-ir-strategy.h"

IRModuleDeclarationNode* ModuleDeclarationIRStrategy::generate(ASTModuleDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    return new IRModuleDeclarationNode(node);
}
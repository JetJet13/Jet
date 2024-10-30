//
// Created by Johny Georges on 2024-10-30.
//

#include "import-single-module-declaration-ir-strategy.h"

IRImportSingleModuleDeclarationNode* ImportSingleModuleDeclarationIRStrategy::generate(ASTImportSingleModuleDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    return new IRImportSingleModuleDeclarationNode(node);
}
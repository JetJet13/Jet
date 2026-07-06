//
// Created by Johny Georges on 2024-10-30.
//

#include "import-single-module-declaration-ir-strategy.h"

std::shared_ptr<IRImportSingleModuleDeclarationNode> ImportSingleModuleDeclarationIRStrategy::generate(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return std::make_shared<IRImportSingleModuleDeclarationNode>(node);
}
//
// Created by Johny Georges on 2024-10-30.
//

#include "import-single-module-declaration-ir-strategy.h"

IRImportSingleModuleDeclarationNode* ImportSingleModuleDeclarationIRStrategy::generate(ASTImportSingleModuleDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return new IRImportSingleModuleDeclarationNode(node);
}
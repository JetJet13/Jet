//
// Created by Johny Georges on 2024-05-02.
//

#include "import-single-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"

void ImportSingleModuleDeclarationIdStrategy::assign(ASTNode* node) {
    auto importSingleModuleDeclarationNode = (ASTImportSingleModuleDeclarationNode*)node;
    importSingleModuleDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    importSingleModuleDeclarationNode
                            ->getModuleName()
                            ->getIdentifier()
                            ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}
//
// Created by Johny Georges on 2024-10-23.
//

#ifndef JETLANG_IMPORT_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_IMPORT_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../../../ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../type-signature-lookup-table/literal-type-signature-lookup-table/literal-type-signature-lookup-table.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "../type-signature-strategy-provider.h"

class ImportTypeSignatureStrategy {
public:
    void assignAndAddToScope(ASTImportSingleModuleDeclarationNode* importSingleModuleDeclarationNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_IMPORT_TYPE_SIGNATURE_STRATEGY_H

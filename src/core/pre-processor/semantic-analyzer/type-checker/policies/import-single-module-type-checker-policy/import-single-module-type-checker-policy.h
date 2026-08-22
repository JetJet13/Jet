//
// Created by Johny Georges on 2024-10-28.
//

#ifndef JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H
#define JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ImportSingleModuleTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTImportSingleModuleDeclarationNode> importSingleModuleDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H

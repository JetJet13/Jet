//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ModuleDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleDeclarationNode> moduleDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H

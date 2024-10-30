//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

namespace ModuleDeclarationTypeCheckerPolicy {
    void apply(ASTModuleDeclarationNode* moduleDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_MODULE_DECLARATION_TYPE_CHECKER_POLICY_H

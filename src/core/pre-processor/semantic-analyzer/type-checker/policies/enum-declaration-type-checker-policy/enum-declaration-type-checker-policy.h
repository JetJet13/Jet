//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

namespace EnumDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTEnumDeclarationNode> enumDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H

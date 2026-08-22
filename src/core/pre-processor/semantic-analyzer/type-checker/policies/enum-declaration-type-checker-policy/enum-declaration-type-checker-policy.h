//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace EnumDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTEnumDeclarationNode> enumDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_ENUM_DECLARATION_TYPE_CHECKER_POLICY_H

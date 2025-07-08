//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

namespace CustomTypeDeclarationTypeCheckerPolicy {
    void apply(ASTCustomTypeDeclarationNode* customTypeDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CUSTOM_TYPE_DECLARATION_TYPE_CHECKER_POLICY_H

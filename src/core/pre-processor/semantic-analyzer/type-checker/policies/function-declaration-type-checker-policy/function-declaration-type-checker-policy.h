//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../types/type-checker-result/type-checker-result.h"
#include "../../rules/type-checker-rule-provider.h"

namespace FunctionDeclarationTypeCheckerPolicy {
    void apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H

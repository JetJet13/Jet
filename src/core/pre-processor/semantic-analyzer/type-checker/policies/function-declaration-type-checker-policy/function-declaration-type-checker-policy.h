//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../types/type-checker-result/type-checker-result.h"
#include "../../types/type-checker-rules/type-checker-rule-list.h"

namespace FunctionDeclarationTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionDeclarationNode* functionDeclarationNode, TypeCheckerRuleList* rules);
};

#endif //JETLANG_FUNCTION_DECLARATION_TYPE_CHECKER_POLICY_H

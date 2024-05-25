//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../types/type-checker-result/type-checker-result.h"
#include "../../types/type-checker-rules/type-checker-rule-list.h"

namespace VariableDeclarationTypeCheckerPolicy {
    TypeCheckerResult apply(ASTVariableDeclarationNode* variableDeclarationNode, TypeCheckerRuleList* rules);
};

#endif //JETLANG_VARIABLE_DECLARATION_TYPE_CHECKER_POLICY_H

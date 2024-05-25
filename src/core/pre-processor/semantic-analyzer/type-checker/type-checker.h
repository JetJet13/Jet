//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_TYPE_CHECKER_H
#define JETLANG_TYPE_CHECKER_H

#include "../../../ast/ast-nodes/ast-node.h"
#include "types/type-checker-result/type-checker-result.h"
#include "types/type-checker-rules/type-checker-rule-list.h"

namespace TypeChecker {
    TypeCheckerResult applyPolicyTo(ASTNode* node, TypeCheckerRuleList* rules);
};

#endif //JETLANG_TYPE_CHECKER_H

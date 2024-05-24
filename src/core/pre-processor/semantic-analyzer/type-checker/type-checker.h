//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_TYPE_CHECKER_H
#define JETLANG_TYPE_CHECKER_H

#include "types/type-checker-result.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "policies/variable-declaration-type-checker-policy/variable-declaration-type-checker-policy.h"

class TypeChecker {
public:
    TypeCheckerResult applyPolicyFor(ASTNode* node);
};

#endif //JETLANG_TYPE_CHECKER_H

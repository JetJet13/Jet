//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_TYPE_CHECKER_H
#define JETLANG_TYPE_CHECKER_H

#include "../../../ast/ast-nodes/ast-node.h"
#include "types/type-checker-result/type-checker-result.h"


namespace TypeChecker {
    void applyPolicyTo(ASTNode* node, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_TYPE_CHECKER_H

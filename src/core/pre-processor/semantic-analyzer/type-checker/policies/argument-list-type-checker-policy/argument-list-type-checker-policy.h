//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H
#define JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"

namespace ArgumentListTypeCheckerPolicy {
    void apply(ASTFunctionArgumentListNode* functionArgumentList, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H

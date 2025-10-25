//
// Created by Johny Georges on 2025-10-25.
//

#include "argument-list-type-checker-policy.h"
#include "../../type-checker.h"

namespace ArgumentListTypeCheckerPolicy {
    void apply(ASTFunctionArgumentListNode* functionArgumentList, TypeCheckerResult* typeCheckerResult) {
        for (auto argument : *functionArgumentList->getArguments()) {
            TypeChecker::applyPolicyTo(argument->getArgument(), typeCheckerResult);
        }
    }
}
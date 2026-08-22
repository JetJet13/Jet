//
// Created by Johny Georges on 2025-10-25.
//

#include "argument-list-type-checker-policy.h"
#include "../../type-checker.h"

namespace ArgumentListTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionArgumentListNode> functionArgumentList, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        for (auto argument : *functionArgumentList->getArguments()) {
            TypeChecker::applyPolicyTo(argument->getArgument(), typeCheckerResult, fileScope);
        }
    }
}
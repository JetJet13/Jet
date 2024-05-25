//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-list-type-checker-policy.h"
#include "../../type-checker.h"

namespace ParameterListTypeCheckerPolicy {
    TypeCheckerResult apply(ASTFunctionParameterListNode* functionParameterList, TypeCheckerRuleList* rules) {
        auto typeCheckerResult = TypeCheckerResult();

        for (auto parameter : functionParameterList->getParameters()) {
            typeCheckerResult.combine(TypeChecker::applyPolicyTo(parameter, rules));
        }

        return typeCheckerResult;
    }
}
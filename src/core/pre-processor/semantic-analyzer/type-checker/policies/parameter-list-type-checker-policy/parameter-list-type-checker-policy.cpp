//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-list-type-checker-policy.h"
#include "../../type-checker.h"

namespace ParameterListTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionParameterListNode> functionParameterList, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        for (auto parameter : functionParameterList->getParameters()) {
            TypeChecker::applyPolicyTo(parameter, typeCheckerResult, fileScope);
        }
    }
}
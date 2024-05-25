//
// Created by Johny Georges on 2024-05-25.
//

#include "parameter-list-type-checker-policy.h"
#include "../../types/type-checker-result-factory.h"

TypeCheckerResult ParameterListTypeCheckerPolicy::verify(ASTFunctionParameterListNode* functionParameterList) {
    auto errors = std::vector<std::string>();

    if (errors.empty()) {
        return TypeCheckerResultFactory::createOkResult();
    }
    return TypeCheckerResultFactory::createErrorResult(errors);
}
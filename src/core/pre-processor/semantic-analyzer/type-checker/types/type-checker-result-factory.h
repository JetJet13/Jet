//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RESULT_FACTORY_H
#define JETLANG_TYPE_CHECKER_RESULT_FACTORY_H

#include "type-checker-result/type-checker-result.h"

namespace TypeCheckerResultFactory {
    static TypeCheckerResult createOkResult() {
        return TypeCheckerResult();
    }
    static TypeCheckerResult createErrorResult(std::vector<std::string> errors) {
        return TypeCheckerResult(errors);
    }
}

#endif //JETLANG_TYPE_CHECKER_RESULT_FACTORY_H

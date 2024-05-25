//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RESULT_FACTORY_H
#define JETLANG_TYPE_CHECKER_RESULT_FACTORY_H

namespace TypeCheckerResultFactory {
    static TypeCheckerResult createOkResult() {
        return {
            .ok = true,
            .errors = {}
        };
    }
    static TypeCheckerResult createErrorResult(std::vector<std::string> errors) {
        return {
            .ok = false,
            .errors = errors
        };
    }
}

#endif //JETLANG_TYPE_CHECKER_RESULT_FACTORY_H

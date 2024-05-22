//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_TYPE_CHECKER_RESULT_H
#define JETLANG_TYPE_CHECKER_RESULT_H

#include <vector>

struct TypeCheckerResult {
    bool ok;
    std::vector<std::string> errors;
};

#endif //JETLANG_TYPE_CHECKER_RESULT_H

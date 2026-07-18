//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RESULT_H
#define JETLANG_TYPE_CHECKER_RESULT_H

#include <vector>
#include <string>
#include "../../../types/type-check-error/type-check-error.h"

class TypeCheckerResult {
private:
    std::vector<std::shared_ptr<TypeCheckError>> _errors;
public:
    TypeCheckerResult();
    TypeCheckerResult(std::vector<std::shared_ptr<TypeCheckError>> errors);
    TypeCheckerResult* addError(std::shared_ptr<TypeCheckError> error);
    TypeCheckerResult* merge(TypeCheckerResult* other);
    bool ok();
    std::vector<std::shared_ptr<TypeCheckError>>* getErrors();
    TypeCheckerResult* combine(TypeCheckerResult other);
    void printErrors();
};

#endif //JETLANG_TYPE_CHECKER_RESULT_H

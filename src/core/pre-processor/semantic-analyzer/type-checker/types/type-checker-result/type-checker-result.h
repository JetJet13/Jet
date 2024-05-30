//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RESULT_H
#define JETLANG_TYPE_CHECKER_RESULT_H

#include <vector>
#include <string>

class TypeCheckerResult {
private:
    std::vector<std::string> _errors;
public:
    TypeCheckerResult();
    TypeCheckerResult(std::vector<std::string> errors);
    TypeCheckerResult* addError(std::string error);
    bool ok();
    std::vector<std::string>* getErrors();
    TypeCheckerResult* combine(TypeCheckerResult other);
    void print();
};

#endif //JETLANG_TYPE_CHECKER_RESULT_H

//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-result.h"

TypeCheckerResult::TypeCheckerResult() {
    _errors = std::vector<std::string>();
}

TypeCheckerResult::TypeCheckerResult(std::vector<std::string> errors) {
    _errors = errors;
}

TypeCheckerResult* TypeCheckerResult::addError(std::string error) {
    _errors.push_back(error);
    return this;
}

bool TypeCheckerResult::ok() {
    return _errors.empty();
}

std::vector<std::string>* TypeCheckerResult::getErrors() {
    return &_errors;
}

TypeCheckerResult* TypeCheckerResult::combine(TypeCheckerResult other) {
    for (auto error : *other.getErrors()) {
        _errors.push_back(error);
    }
    return this;
}

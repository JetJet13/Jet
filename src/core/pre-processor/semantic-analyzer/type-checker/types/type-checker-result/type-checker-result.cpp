//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-result.h"
#include "../../../../../../shared/utils/logger/logger.h"

TypeCheckerResult::TypeCheckerResult() {
    _errors = std::vector<std::shared_ptr<TypeCheckError>>();
}

TypeCheckerResult::TypeCheckerResult(std::vector<std::shared_ptr<TypeCheckError>> errors) {
    _errors = errors;
}

TypeCheckerResult* TypeCheckerResult::addError(std::shared_ptr<TypeCheckError> error) {
    _errors.push_back(error);
    return this;
}

TypeCheckerResult* TypeCheckerResult::merge(TypeCheckerResult* other) {
    auto otherErrors = other->getErrors();
    _errors.insert(_errors.end(), otherErrors->begin(), otherErrors->end());
    return this;
}

bool TypeCheckerResult::ok() {
    return _errors.empty();
}

std::vector<std::shared_ptr<TypeCheckError>>* TypeCheckerResult::getErrors() {
    return &_errors;
}

TypeCheckerResult* TypeCheckerResult::combine(TypeCheckerResult other) {
    for (auto error : *other.getErrors()) {
        _errors.push_back(error);
    }
    return this;
}

void TypeCheckerResult::printErrors() {
    Logger::log("\n");
    for (const auto& error : _errors) {
        Logger::log("File", error.get()->getFilePath());
        Logger::log("TypeError", error.get()->getMessage());
    }
    Logger::log("\n");
}
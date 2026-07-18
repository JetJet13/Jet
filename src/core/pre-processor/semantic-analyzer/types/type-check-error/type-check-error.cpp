//
// Created by Johny Georges on 2026-07-18.
//

#include "type-check-error.h"

TypeCheckError::TypeCheckError(std::string message, std::string filePath) {
    _message = message;
    _filePath = filePath;
}

std::string TypeCheckError::getMessage() {
    return _message;
}

std::string TypeCheckError::getFilePath() {
    return _filePath;
}
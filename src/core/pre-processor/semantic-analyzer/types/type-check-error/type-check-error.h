//
// Created by Johny Georges on 2026-07-18.
//

#ifndef JETLANG_TYPE_CHECK_ERROR_H
#define JETLANG_TYPE_CHECK_ERROR_H

#include <string>

class TypeCheckError {
private:
    std::string _message;
    std::string _filePath;
public:
    TypeCheckError(std::string message, std::string filePath);
    std::string getMessage();
    std::string getFilePath();
};

#endif //JETLANG_TYPE_CHECK_ERROR_H

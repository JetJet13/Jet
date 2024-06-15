//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_FILE_EQUALITY_CHECKER_H
#define JETLANG_FILE_EQUALITY_CHECKER_H

#include <string>

class FileEqualityChecker {
public:
    bool areFilesEqual(std::string filePath, std::string otherFilePath);
};

#endif //JETLANG_FILE_EQUALITY_CHECKER_H

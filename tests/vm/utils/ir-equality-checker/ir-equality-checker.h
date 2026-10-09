//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_IR_EQUALITY_CHECKER_H
#define JETLANG_IR_EQUALITY_CHECKER_H

#include <string>
#include <vector>
#include <set>

class FileEqualityChecker {
public:
    bool areFilesEqual(std::string filePath, std::string otherFilePath);
};

#endif //JETLANG_IR_EQUALITY_CHECKER_H

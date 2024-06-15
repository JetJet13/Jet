//
// Created by Johny Georges on 2024-06-15.
//

#include <fstream>
#include "file-equality-checker.h"
#include "../../../../../src/shared/utils/file-io/file-io.h"
#include "../../../../../src/shared/utils/logger/logger.h"

bool FileEqualityChecker::areFilesEqual(std::string filePath, std::string otherFilePath) {
    std::ifstream fileStream = FileIO::readFile(filePath);
    std::ifstream otherFileStream = FileIO::readFile(otherFilePath);

    std::string fileLine;
    std::string otherFileLine;
    auto result = true;
    while (fileStream.good() || otherFileStream.good()) {
        std::getline(fileStream, fileLine);
        std::getline(otherFileStream, otherFileLine);
        Logger::log("----------");
        Logger::log("fileLine", fileLine);
        Logger::log("otherFileLine", otherFileLine);
        if (fileLine != otherFileLine) {
            result = false;
            break;
        }
    }
    fileStream.close();
    otherFileStream.close();
    return result;
}
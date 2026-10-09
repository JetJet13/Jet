// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-06-15.
//

#include <fstream>
#include "ir-equality-checker.h"
#include "../../../../src/shared/utils/file-io/file-io.h"
#include "../../../../src/shared/utils/logger/logger.h"

bool FileEqualityChecker::areFilesEqual(std::string filePath, std::string otherFilePath) {
    std::ifstream fileStream = FileIO::readFile(filePath);
    std::ifstream otherFileStream = FileIO::readFile(otherFilePath);
    auto visitedTypes = std::set<std::string>();
    auto visitedOtherTypes = std::set<std::string>();
    std::string fileLine;
    std::string otherFileLine;
    auto result = true;
    while (fileStream.good() || otherFileStream.good()) {
        std::getline(fileStream, fileLine);
        std::getline(otherFileStream, otherFileLine);
        Logger::log("----------");
        Logger::log("fileLine", fileLine);
        Logger::log("otherFileLine", otherFileLine);
        auto skipFileLineEqualityCheck = false;
        if (!fileLine.empty() && fileLine.find("= type ", 0) != std::string::npos) {
            visitedTypes.insert(fileLine);
            skipFileLineEqualityCheck = true;
        }

        if (!otherFileLine.empty() && otherFileLine.find("= type ", 0) != std::string::npos) {
            visitedOtherTypes.insert(fileLine);
            skipFileLineEqualityCheck = true;
        }

        if (!skipFileLineEqualityCheck && fileLine != otherFileLine) {
            result = false;
            break;
        }

    }
    fileStream.close();
    otherFileStream.close();

    // llvm types are printed in a non-deterministic way, so we use std::set to ensure
    // that all types exist in both files
    return result && visitedTypes == visitedOtherTypes;
}
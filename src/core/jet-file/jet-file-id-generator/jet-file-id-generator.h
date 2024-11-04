//
// Created by Johny Georges on 2024-11-04.
//

#ifndef JETLANG_JET_FILE_ID_GENERATOR_H
#define JETLANG_JET_FILE_ID_GENERATOR_H

#include <string>
#include <filesystem>

class JetFileIdGenerator {
public:
    static std::string generate(std::filesystem::path* path);
};
#endif //JETLANG_JET_FILE_ID_GENERATOR_H

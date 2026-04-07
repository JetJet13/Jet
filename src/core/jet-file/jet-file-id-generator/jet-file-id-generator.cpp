//
// Created by Johny Georges on 2024-11-04.
//

#include "jet-file-id-generator.h"

std::string JetFileIdGenerator::generate(std::filesystem::path* path) {
    return std::filesystem::canonical(*path).string();
}
//
// Created by Johny Georges on 2024-11-04.
//

#include "jet-file-id-generator.h"

std::string JetFileIdGenerator::generate(std::filesystem::path* path) {
    return path->root_path().string() + path->parent_path().string() + path->filename().string();
}
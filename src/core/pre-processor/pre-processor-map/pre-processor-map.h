//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_PRE_PROCESSOR_MAP_H
#define JETLANG_PRE_PROCESSOR_MAP_H

#include <unordered_map>
#include <vector>
#include <optional>
#include <filesystem>
#include "../../jet-file/jet-file.h"

class PreProcessorMap {
private:
    std::unordered_map<std::string, std::shared_ptr<JetFile>> _graph;
public:
    PreProcessorMap();
    std::optional<std::shared_ptr<JetFile>> findByFilePath(std::string filePath);
    PreProcessorMap* insert(std::shared_ptr<JetFile> jetFile);

};

#endif //JETLANG_PRE_PROCESSOR_MAP_H

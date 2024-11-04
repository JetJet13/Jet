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
    std::unordered_map<std::string, JetFile*> _graph;
public:
    PreProcessorMap();
    std::optional<JetFile*> findByFilePath(std::string filePath);
    PreProcessorMap* insert(JetFile* jetFile);

};

#endif //JETLANG_PRE_PROCESSOR_MAP_H

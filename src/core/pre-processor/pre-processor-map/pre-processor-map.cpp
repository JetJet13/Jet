//
// Created by Johny Georges on 2024-05-01.
//

#include "pre-processor-map.h"
#include "../../jet-file/jet-file-id-generator/jet-file-id-generator.h"

PreProcessorMap::PreProcessorMap() {
    _graph = std::unordered_map<std::string, std::shared_ptr<JetFile>>();
}

PreProcessorMap* PreProcessorMap::insert(std::shared_ptr<JetFile> jetFile) {
    _graph.insert(std::pair(jetFile->getId(), jetFile));
    return this;
}

std::optional<std::shared_ptr<JetFile>> PreProcessorMap::findByFilePath(std::string filePath) {
    auto id = JetFileIdGenerator::generate(std::filesystem::path(filePath));
    auto result = _graph.find(filePath);
    if (result == _graph.end()) {
        return {};
    } else {
        return result->second;
    }
}
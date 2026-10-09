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
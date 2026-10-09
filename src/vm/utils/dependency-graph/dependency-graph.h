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
// Created by Johny Georges on 2026-04-04.
//

#ifndef JETLANG_DEPENDENCY_GRAPH_H
#define JETLANG_DEPENDENCY_GRAPH_H

#include <set>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <stack>
#include "../../../core/jet-file/jet-file.h"


class DependencyGraph {
private:
    std::unordered_map<std::string, std::shared_ptr<std::set<std::shared_ptr<JetFile>>>> _directDependencyMap;
    std::unordered_map<std::string, uint64_t> _totalDependencyMap;
    std::vector<std::pair<uint64_t, std::shared_ptr<JetFile>>> _totalCounts;
    std::vector<std::shared_ptr<JetFile>> _importFreeFiles;
    uint64_t _priorityCounter = 1;
    std::set<std::string> _visited;
    uint64_t setAndReturnTotalDependents(std::shared_ptr<JetFile> jetFile);
public:
    DependencyGraph();
    std::shared_ptr<std::vector<std::shared_ptr<JetFile>>> getPrioritizedList();
    void insert(std::shared_ptr<JetFile> jetFile);
    void insertImport(std::shared_ptr<JetFile> jetFile, std::shared_ptr<JetFile> importedJetFile);
    void prioritize();
    void dump();
};

#endif //JETLANG_DEPENDENCY_GRAPH_H

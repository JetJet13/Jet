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

#include "dependency-graph.h"
#include "../../../shared/utils/logger/logger.h"

// step 1. populate directDependents list
// step 2. populate totalDependents list
// step 3. prioritize by totalDependents count ( the higher the count, the higher the priority)

DependencyGraph::DependencyGraph() {
    _directDependencyMap = std::unordered_map<std::string, std::shared_ptr<std::set<std::shared_ptr<JetFile>>>>();
    _totalDependencyMap = std::unordered_map<std::string, uint64_t>();
    _totalCounts = std::vector<std::pair<uint64_t, std::shared_ptr<JetFile>>>();
    _visited = std::set<std::string>();
    _importFreeFiles = std::vector<std::shared_ptr<JetFile>>();
}

std::shared_ptr<std::vector<std::shared_ptr<JetFile>>> DependencyGraph::getPrioritizedList() {
    auto prioritizedList = std::make_shared<std::vector<std::shared_ptr<JetFile>>>();
    for (auto keyValue : _totalCounts) {
        prioritizedList->push_back(keyValue.second);
    }
    return prioritizedList;
}

void DependencyGraph::insert(std::shared_ptr<JetFile> jetFile) {
    auto id = jetFile->getId();
    auto existingRecord = _directDependencyMap.find(id);
    if (existingRecord != _directDependencyMap.end()) {
        return;
    }
    _directDependencyMap.insert(std::pair(id, std::make_shared<std::set<std::shared_ptr<JetFile>>>()));
    _totalDependencyMap.insert(std::pair(id, 0));
    if (!jetFile->hasImports()) {
        _importFreeFiles.push_back(jetFile);
    }
    for (auto importedJetFile : *jetFile->getImportedFiles()) {
        this->insertImport(jetFile, importedJetFile);
    }
}

void DependencyGraph::insertImport(std::shared_ptr<JetFile> jetFile, std::shared_ptr<JetFile> importedJetFile) {
    this->insert(importedJetFile);
    _directDependencyMap.find(importedJetFile->getId())->second->insert(jetFile);
}

void DependencyGraph::prioritize() {
    for (auto importFreeFile : _importFreeFiles) {
        this->setAndReturnTotalDependents(importFreeFile);
    }
    std::sort(
        _totalCounts.begin(),
        _totalCounts.end(),
        [](const std::pair<uint64_t, std::shared_ptr<JetFile>>& a, const std::pair<uint64_t, std::shared_ptr<JetFile>>& b) {
            if (a.first == b.first) return a.second->getId() < b.second->getId(); // if total count equal, sort alphabetically
            return a.first > b.first;  // sort by desc order
        }
    );
}

uint64_t DependencyGraph::setAndReturnTotalDependents(std::shared_ptr<JetFile> jetFile) {
    if (_visited.find(jetFile->getId()) != _visited.end()) {
        return _totalDependencyMap.find(jetFile->getId())->second;
    }
    uint64_t total = _directDependencyMap.find(jetFile->getId())->second->size();
    for (auto dependents : *_directDependencyMap.find(jetFile->getId())->second) {
        total += this->setAndReturnTotalDependents(dependents);
    }
    _totalDependencyMap[jetFile->getId()] = total;
    _visited.insert(jetFile->getId());
    _totalCounts.push_back(std::pair(total, jetFile));
    return _totalDependencyMap.find(jetFile->getId())->second;
}

void DependencyGraph::dump() {
    Logger::log("=== IMPORT GRAPH DUMP ==");

    for (auto keyValue : _directDependencyMap) {
        Logger::log("File", keyValue.first);
        if (keyValue.second->empty()) {
            Logger::log("HAS NO DEPENDENTS");
        } else {
            Logger::log("=========== DEPENDENTS ===========");
        }
        for (auto dependent : *keyValue.second) {
            Logger::log(dependent->getId());
        }
        Logger::log("================================ \n");
    }
    Logger::log("=========== TOTAL DEPENDENCY COUNT MAP ===========");
    for (auto keyValue : _totalDependencyMap) {
        Logger::log(keyValue.second, keyValue.first);
    }
    Logger::log("========================");
}
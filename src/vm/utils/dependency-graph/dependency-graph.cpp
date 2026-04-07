//
// Created by Johny Georges on 2026-04-04.
//

#include "dependency-graph.h"
#include "../../../shared/utils/logger/logger.h"

// step 1. populate directDependents list
// step 2. populate totalDependents list
// step 3. prioritize by totalDependents count ( the higher the count, the higher the priority)

DependencyGraph::DependencyGraph() {
    _directDependencyMap = std::unordered_map<std::string, std::set<JetFile*>*>();
    _totalDependencyMap = std::unordered_map<std::string, unsigned long>();
    _priorityJetFileMap = std::unordered_map<unsigned long, JetFile*>();
    _totalCounts = std::vector<unsigned long>();
    _visited = std::set<std::string>();
    _importFreeFiles = std::vector<JetFile*>();
}

std::vector<JetFile*>* DependencyGraph::getPrioritizedList() {
    auto prioritizedList = new std::vector<JetFile*>();
    for (auto total : _totalCounts) {
        prioritizedList->push_back(_priorityJetFileMap.find(total)->second);

    }
    return prioritizedList;
}

void DependencyGraph::insert(JetFile* jetFile) {
    auto id = jetFile->getId();
    auto existingRecord = _directDependencyMap.find(id);
    if (existingRecord != _directDependencyMap.end()) {
        return;
    }
    _directDependencyMap.insert(std::pair(id, new std::set<JetFile*>()));
    _totalDependencyMap.insert(std::pair(id, 0));
    if (!jetFile->hasImports()) {
        _importFreeFiles.push_back(jetFile);
    }
    for (auto importedJetFile : *jetFile->getImportedFiles()) {
        this->insertImport(jetFile, importedJetFile);
    }
}

void DependencyGraph::insertImport(JetFile* jetFile, JetFile* importedJetFile) {
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
        [](const unsigned long& a, const unsigned long& b) {
          return a > b;  // sort by desc order
        }
    );
}

unsigned long DependencyGraph::setAndReturnTotalDependents(JetFile* jetFile) {
    if (_visited.find(jetFile->getId()) != _visited.end()) {
        return _totalDependencyMap.find(jetFile->getId())->second;
    }
    unsigned long total = _directDependencyMap.find(jetFile->getId())->second->size();
    for (auto dependents : *_directDependencyMap.find(jetFile->getId())->second) {
        total += this->setAndReturnTotalDependents(dependents);
    }
    _totalDependencyMap[jetFile->getId()] = total;
    _visited.insert(jetFile->getId());
    _priorityJetFileMap.insert(std::pair(total, jetFile));
    _totalCounts.push_back(total);
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
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

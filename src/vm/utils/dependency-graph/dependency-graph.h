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
    std::unordered_map<std::string, std::set<JetFile*>*> _directDependencyMap;
    std::unordered_map<std::string, unsigned long> _totalDependencyMap;
    std::unordered_map<unsigned long, JetFile*> _priorityJetFileMap;
    std::vector<unsigned long> _totalCounts;
    std::vector<JetFile*> _importFreeFiles;
    unsigned long _priorityCounter = 1;
    std::set<std::string> _visited;
    unsigned long setAndReturnTotalDependents(JetFile* jetFile);
public:
    DependencyGraph();
    std::vector<JetFile*>* getPrioritizedList();
    void insert(JetFile* jetFile);
    void insertImport(JetFile* jetFile, JetFile* importedJetFile);
    void prioritize();
    void dump();
};

#endif //JETLANG_DEPENDENCY_GRAPH_H

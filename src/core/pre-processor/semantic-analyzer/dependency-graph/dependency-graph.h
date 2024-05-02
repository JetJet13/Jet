//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_DEPENDENCY_GRAPH_H
#define JETLANG_DEPENDENCY_GRAPH_H

#include <unordered_map>
#include <vector>
#include <optional>

class DependencyGraph {
private:
    std::unordered_map<int, std::vector<int>> _graph;
    std::optional<std::vector<int>> find(int key);
public:
    DependencyGraph();
    DependencyGraph* insert(int key, int dependency);
    bool hasDependency(int key, int dependency);

};

#endif //JETLANG_DEPENDENCY_GRAPH_H

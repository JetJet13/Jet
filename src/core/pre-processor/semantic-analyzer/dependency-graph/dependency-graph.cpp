//
// Created by Johny Georges on 2024-05-01.
//

#include "dependency-graph.h"

DependencyGraph::DependencyGraph() {
    _graph = std::unordered_map<int, std::vector<int>>();
}

DependencyGraph* DependencyGraph::insert(int key, int dependency) {
    auto item = this->find(key);
    if (item) {
        item.value().push_back(dependency);
    } else {
        _graph.insert(std::pair<int, std::vector<int>>(key, { dependency }));
    }
    return this;
}

bool DependencyGraph::hasDependency(int key, int dependency) {
    auto dependencies = this->find(key);
    if (!dependencies) {
        return false;
    }
    return std::find(dependencies->begin(), dependencies->end(), dependency) != dependencies->end();
}

std::optional<std::vector<int>> DependencyGraph::find(int key) {
    auto result = _graph.find(key);
    if (result == _graph.end()) {
        return {};
    } else {
        return result->second;
    }
}
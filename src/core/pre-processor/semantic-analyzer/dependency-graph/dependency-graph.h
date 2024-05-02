//
// Created by Johny Georges on 2024-05-01.
//

#ifndef JETLANG_DEPENDENCY_GRAPH_H
#define JETLANG_DEPENDENCY_GRAPH_H

#include <unordered_map>
#include <vector>
#include <optional>
#include "../../../ast/types/ast-node-type.h"

class DependencyGraph {
private:
    std::unordered_map<ASTNodeType, std::vector<ASTNodeType>*, std::hash<int>> _followAstNodeMap;
public:
    DependencyGraph();
    DependencyGraph* insert(int key, int dependency);
    std::optional<int> getDependency(int key, int dependency);
};

#endif //JETLANG_DEPENDENCY_GRAPH_H

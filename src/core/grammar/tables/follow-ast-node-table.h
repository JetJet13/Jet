//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_FOLLOW_AST_NODE_TABLE_H
#define JETLANG_FOLLOW_AST_NODE_TABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../../ast/types/ast-node-type.h"


class FollowASTNodeTable {
private:
    std::unordered_map<ASTNodeType, std::vector<ASTNodeType>*, std::hash<int>> _followAstNodeMap;
    void init();
    void add(ASTNodeType astNodeType, std::vector<ASTNodeType>* followAstNodeTypes);
public:
    FollowASTNodeTable();
    bool isValidFollowASTNode(ASTNodeType followAstNodeType, ASTNodeType astNodeType);
};

#endif //JETLANG_FOLLOW_AST_NODE_TABLE_H

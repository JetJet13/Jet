//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_HANDLE_H
#define JETLANG_HANDLE_H

#include <deque>
#include <vector>
#include "../../../ast/ast-nodes/ast-node.h"

class Handle {
private:
    std::deque<ASTNode*> _handle;
public:
    Handle();
    std::optional<ASTNode*> at(int index);
    bool isNodeTypeAt(int index, ASTNodeType astNodeType);
    bool isEmpty();
    void clear();
    int size();
    std::vector<ASTNode*> getFirstNodes(int numNodesToGet);
    void removeFirstNodes(int numNodesToRemove);
    void push(ASTNode* node);
};

#endif //JETLANG_HANDLE_H

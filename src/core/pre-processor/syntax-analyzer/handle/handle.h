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
    std::optional<ASTNode*> _lastReducedNode;
    std::optional<ASTNode*> _peekNode;
public:
    Handle();
    std::optional<ASTNode*> at(int index);
    std::optional<ASTNode*> first();
    std::optional<ASTNode*> last();
    bool isNodeTypeAt(int index, ASTNodeType astNodeType);
    bool isEmpty();
    bool isTerminatorOnlyNode();
    void clear();
    int size();
    std::vector<ASTNode*> getFirstNodes(int numNodesToGet);
    void removeFirstNodes(int numNodesToRemove);
    void append(ASTNode* node);
    void prepend(ASTNode* node);
    std::optional<ASTNode*> getLastReducedNode();
    void setLastReducedNode(std::optional<ASTNode*> peekNode);
    void clearLastReducedNode();
    std::optional<ASTNode*> getPeekNode();
    void setPeekNode(std::optional<ASTNode*> peekNode);
    void clearPeekNode();
    void print();
};

#endif //JETLANG_HANDLE_H

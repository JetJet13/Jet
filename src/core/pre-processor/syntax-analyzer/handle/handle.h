//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_HANDLE_H
#define JETLANG_HANDLE_H

#include <deque>
#include <vector>
#include "../../../ast/ast-nodes/ast-node.h"
#include "types/handle-mode.h"

class Handle {
private:
    std::deque<ASTNode*> _handle;
    std::optional<ASTNode*> _lastReducedNode;
    std::optional<ASTNode*> _peekNode;
    HandleMode _mode;
    void determineMode();
public:
    Handle();
    std::optional<ASTNode*> at(int index);
    std::optional<ASTNode*> first();
    std::optional<ASTNode*> last();
    HandleMode getMode();
    bool isNodeTypeAt(int index, ASTNodeType astNodeType);
    bool isEmpty();
    bool isTerminatorMode();
    bool isTerminatorOnlyNode();
    bool isGroupEnclosed();
    bool isGroupingMode();
    bool isGroupingOnlyNode();
    bool isArrayEnclosed();
    bool isArrayMode();
    bool isArrayOnlyNode();
    bool isFunctionBlockOnlyNode();
    bool isStructEnclosed();
    bool isStructMode();
    bool isStructEndOnlyNode();
    bool isFunctionParameterListEnclosed();
    bool isFunctionParameterListMode();
    bool isFunctionParameterListEndOnlyNode();
    bool isNormalMode();
    bool isNotNormalMode();
    void clear();
    unsigned long size();
    std::vector<ASTNode*> getFirstNodes(int numNodesToGet);
    void removeFirstNodes(int numNodesToRemove);
    void removeFirstNode();
    void removeLastNode();
    void append(ASTNode* node);
    void prepend(ASTNode* node);
    void replace(int index, ASTNode* newNode);
    std::optional<ASTNode*> getLastReducedNode();
    void setLastReducedNode(std::optional<ASTNode*> peekNode);
    void clearLastReducedNode();
    std::optional<ASTNode*> getPeekNode();
    void setPeekNode(std::optional<ASTNode*> peekNode);
    void clearPeekNode();
    std::optional<ASTNode*> getPrevNodeFor(int index);
    std::optional<ASTNode*> getNextNodeFor(int index);
    void print();
};

#endif //JETLANG_HANDLE_H

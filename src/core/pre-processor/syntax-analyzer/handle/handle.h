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
    std::deque<std::shared_ptr<ASTNode>> _handle;
    std::optional<std::shared_ptr<ASTNode>> _lastReducedNode;
    std::optional<std::shared_ptr<ASTNode>> _peekNode;
public:
    Handle();
    std::optional<std::shared_ptr<ASTNode>> at(int index);
    std::optional<std::shared_ptr<ASTNode>> first();
    std::optional<std::shared_ptr<ASTNode>> last();
    bool isNodeTypeAt(int index, ASTNodeType astNodeType);
    bool isEmpty();
    bool isTerminatorOnlyNode();
    bool isGroupEnclosed();
    bool isArrayEnclosed();
    bool isStructEnclosed();
    bool isStructTypeEnclosed();
    bool isTupleTypeEnclosed();
    bool isFunctionParameterListEnclosed();
    bool isFunctionArgumentListEnclosed();
    bool isEnumKeyValueListEnclosed();
    bool isInterfacePropertyListEnclosed();
    bool isImplementsInterfaceListEnclosed();
    bool isTupleListEnclosed();
    bool isModuleListEnclosed();
    bool isImportModuleListEnclosed();
    bool isLambdaTypeParameterListEnclosed();
    bool isTypeParameterListEnclosed();
    bool hasOneAndOnlyNode();
    void clear();
    void reset();
    unsigned long size();
    std::vector<std::shared_ptr<ASTNode>> getFirstNodes(int numNodesToGet);
    void removeFirstNodes(int numNodesToRemove);
    void removeFirstNode();
    void removeLastNode();
    void append(std::shared_ptr<ASTNode> node);
    void prepend(std::shared_ptr<ASTNode> node);
    void replace(int index, std::shared_ptr<ASTNode> newNode);
    std::optional<std::shared_ptr<ASTNode>> getLastReducedNode();
    void setLastReducedNode(std::optional<std::shared_ptr<ASTNode>> peekNode);
    void clearLastReducedNode();
    std::optional<std::shared_ptr<ASTNode>> getPeekNode();
    void setPeekNode(std::optional<std::shared_ptr<ASTNode>> peekNode);
    void clearPeekNode();
    std::optional<std::shared_ptr<ASTNode>> getPrevNodeFor(int index);
    std::optional<std::shared_ptr<ASTNode>> getNextNodeFor(int index);
    void print();
};

#endif //JETLANG_HANDLE_H

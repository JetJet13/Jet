// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    uint64_t size();
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

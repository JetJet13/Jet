//
// Created by Johny Georges on 2024-06-21.
//

#include "stack-merger.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "../../../../shared/utils/logger/logger.h"

template<class T>
std::stack<T>* StackMerger<T>::merge(std::stack<T>* firstStack, std::stack<T>* secondStack) {
    auto queue = std::deque<T>();
    while (!secondStack->empty()) {
        auto secondStackItem = secondStack->top();
        secondStack->pop();
        queue.push_back(secondStackItem);
    }

    while (!firstStack->empty()) {
        auto firstStackItem = firstStack->top();
        firstStack->pop();
        queue.push_back(firstStackItem);
    }

    auto newStack = new std::stack<T>();
    while (!queue.empty()) {
        auto item = queue.back();
        queue.pop_back();
        newStack->push(item);
    }

    return newStack;
}

template<class T>
std::stack<T>* StackMerger<T>::merge(std::stack<T>* firstStack, std::vector<T> otherVector) {
    auto newStack = new std::stack<T>();
    while (!firstStack->empty()) {
        auto firstStackItem = firstStack->top();
        firstStack->pop();
        newStack->push(firstStackItem);
    }

    for (auto item : otherVector) {
        newStack->push(item);
    }

    return newStack;
}

template<class T>
std::stack<T>* StackMerger<T>::merge(std::vector<T> firstVector, std::stack<T>* otherStack) {
    auto newStack = new std::stack<T>();
    for (auto item : firstVector) {
        Logger::log("StackMerger :: pushing vector item to stack", (std::dynamic_pointer_cast<ASTNode>(item))->toString());
        newStack->push(item);
    }

    while (!otherStack->empty()) {
        auto firstStackItem = otherStack->top();
        otherStack->pop();
        Logger::log("StackMerger :: pushing stack item to stack", (std::dynamic_pointer_cast<ASTNode>(firstStackItem))->toString());
        newStack->push(firstStackItem);
    }
    return newStack;
}

template class StackMerger<std::shared_ptr<ASTNode>>;
//
// Created by Johny Georges on 2024-06-21.
//

#include "stack-merger.h"

template<class T>
std::stack<T> StackMerger<T>::merge(std::stack<T>* firstStack, std::stack<T>* secondStack) {
    auto newStack = std::stack<T>();
    while (!firstStack->empty()) {
        auto firstStackItem = firstStack->top();
        firstStack->pop();
        newStack.push(firstStackItem);
    }

    while (!secondStack->empty()) {
        auto secondStackItem = secondStack->top();
        secondStack->pop();
        newStack.push(secondStackItem);
    }

    return newStack;
}

template<class T>
std::stack<T> StackMerger<T>::merge(std::stack<T>* firstStack, std::vector<T> otherVector) {
    auto newStack = std::stack<T>();
    while (!firstStack->empty()) {
        auto firstStackItem = firstStack->top();
        firstStack->pop();
        newStack.push(firstStackItem);
    }

    for (auto item : otherVector) {
        newStack.push(item);
    }

    return newStack;
}

template<class T>
std::stack<T> StackMerger<T>::merge(std::vector<T> firstVector, std::stack<T>* otherStack) {
    auto newStack = std::stack<T>();
    for (auto item : firstVector) {
        newStack.push(item);
    }

    while (!otherStack->empty()) {
        auto firstStackItem = otherStack->top();
        otherStack->pop();
        newStack.push(firstStackItem);
    }
    return newStack;
}

//template class StackMerger<*>;
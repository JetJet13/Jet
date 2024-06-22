//
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_STACK_MERGER_H
#define JETLANG_STACK_MERGER_H

#include <stack>

template<class T>
class StackMerger {
public:
    static std::stack<T>* merge(std::stack<T>* firstStack, std::stack<T>* secondStack);
    static std::stack<T>* merge(std::stack<T>* firstStack, std::vector<T> otherVector);
    static std::stack<T>* merge(std::vector<T> firstVector, std::stack<T>* otherStack);
};

#endif //JETLANG_STACK_MERGER_H

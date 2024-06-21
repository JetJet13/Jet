//
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_STACK_MERGER_H
#define JETLANG_STACK_MERGER_H

#include <stack>

template<class T>
class StackMerger {
public:
    std::stack<T> static merge(std::stack<T>* firstStack, std::stack<T>* secondStack);
    std::stack<T> static merge(std::stack<T>* firstStack, std::vector<T> otherVector);
    std::stack<T> static merge(std::vector<T> firstVector, std::stack<T>* otherStack);
};

#endif //JETLANG_STACK_MERGER_H

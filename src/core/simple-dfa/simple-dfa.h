//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_SIMPLE_DFA_H
#define JETLANG_SIMPLE_DFA_H

#include <unordered_map>
#include "../type-signature/types/type-source.h"
#include "simple-dfa-node.h"

template<class T, class R>
class SimpleDfa {
private:
    std::unordered_map<T, SimpleDfaNode<T,R>*, std::hash<int>> _startNodes;
    std::optional<SimpleDfaNode<T,R>*> _current;
public:
    SimpleDfa();
    SimpleDfa* insertStartNode(SimpleDfaNode<T,R>* node);
    void reset();
    void init(TypeSource typeSource);
    void determine(R transitionSymbol);
    std::optional<SimpleDfaNode<T,R>*> getCurrentState();
};

#endif //JETLANG_SIMPLE_DFA_H

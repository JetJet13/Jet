//
// Created by Johny Georges on 2024-05-06.
//

#include "simple-dfa.h"

template<class T, class R>
SimpleDfa<T,R>::SimpleDfa() {
    _startNodes = std::unordered_map<T, SimpleDfaNode<T,R>*, std::hash<int>>();
    _current = {};
}

template<class T, class R>
SimpleDfa<T,R>* SimpleDfa<T,R>::insertStartNode(SimpleDfaNode<T,R>* node) {
    _startNodes.insert(std::pair<TypeSource , SimpleDfaNode<T,R>*>(node->getTypeSource(), node));
    return this;
}

template<class T, class R>
void SimpleDfa<T,R>::reset() {
    _current = {};
}

template<class T, class R>
void SimpleDfa<T,R>::init(TypeSource typeSource) {
    auto startNode = _startNodes.find(typeSource);
    if (startNode == _startNodes.end()) {
        throw std::invalid_argument( "no start DFA Node found for TypeSource");
    }

    _current = startNode->second;
}

template<class T, class R>
void SimpleDfa<T,R>::determine(R symbolType) {
    if (!_current) {
        return;
    }

    _current = _current.value()->transition(symbolType);
}

template<class T, class R>
std::optional<SimpleDfaNode<T,R>*> SimpleDfa<T,R>::getCurrentState() {
    return _current;
}
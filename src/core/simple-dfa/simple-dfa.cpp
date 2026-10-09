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
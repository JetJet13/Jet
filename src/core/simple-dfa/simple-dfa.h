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

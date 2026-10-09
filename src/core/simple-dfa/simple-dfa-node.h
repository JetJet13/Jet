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

#ifndef JETLANG_SIMPLE_DFA_NODE_H
#define JETLANG_SIMPLE_DFA_NODE_H

#include <vector>
#include <optional>

template<class T, class R>
struct SimpleDfaTransition;

template<class T, class R>
class SimpleDfaNode {
private:
    std::optional<T> _targetType;
    T _type;
    std::vector<SimpleDfaTransition<T,R>> _transitions;
public:
    SimpleDfaNode(T type, std::optional<T> targetAstNodeType = {});
    SimpleDfaNode* addTransition(SimpleDfaTransition<T,R> transition);
    std::optional<SimpleDfaNode<T,R>*> transition(R transitionSymbol);
    T getType();
    bool hasTarget();
    T getTargetValue();
};

template<class T, class R>
struct SimpleDfaTransition {
    R symbol;
    SimpleDfaNode<T,R>* destination;
};

#endif //JETLANG_SIMPLE_DFA_NODE_H

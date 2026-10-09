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

#include "simple-dfa-node.h"

template<class T, class R>
SimpleDfaNode<T,R>::SimpleDfaNode(T type, std::optional<T> targetType) {
    _type = type;
    _targetType = targetType;
    _transitions = std::vector<SimpleDfaTransition<T,R>>();
}

template<class T, class R>
SimpleDfaNode<T,R>* SimpleDfaNode<T,R>::addTransition(SimpleDfaTransition<T,R> transition) {
    _transitions.push_back(transition);
    return this;
}

template<class T, class R>
std::optional<SimpleDfaNode<T,R>*> SimpleDfaNode<T,R>::transition(R transitionSymbol) {

    for (auto transition : _transitions) {
        if (transition.symbol == transitionSymbol) {
            return transition.destination;
        }
    }

    return {};
}

template<class T, class R>
T SimpleDfaNode<T,R>::getType() {
    return _type;
}

template<class T, class R>
T SimpleDfaNode<T,R>::getTargetValue() {
    return _targetType.value();
}

template<class T, class R>
bool SimpleDfaNode<T,R>::hasTarget() {
    return _targetType.has_value();
}
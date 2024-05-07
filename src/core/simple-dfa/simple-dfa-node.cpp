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
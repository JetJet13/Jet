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

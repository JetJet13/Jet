//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_TRANSITION_FACTORY_H
#define JETLANG_DFA_TRANSITION_FACTORY_H

#include "dfa-node.h"

namespace DFATransitionFactory {
    DFATransition create(std::shared_ptr<DFANode> dfaNode);
}
#endif //JETLANG_DFA_TRANSITION_FACTORY_H

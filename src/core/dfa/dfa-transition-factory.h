//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_TRANSITION_FACTORY_H
#define JETLANG_DFA_TRANSITION_FACTORY_H

#include "dfa-node.h"

namespace DFATransitionFactory {
    DFATransition create(DFANode* dfaNode);
    DFATransition create(ASTNodeType prefix, DFANode* dfaNode);
    DFATransition create(DFANode* dfaNode, ASTNodeType suffix);
    DFATransition create(ASTNodeType prefix, DFANode* dfaNode, ASTNodeType suffix);
}
#endif //JETLANG_DFA_TRANSITION_FACTORY_H

//
// Created by Johny Georges on 2024-02-15.
//

#ifndef JETLANG_DFA_TRANSITION_FACTORY_H
#define JETLANG_DFA_TRANSITION_FACTORY_H

#include "dfa-node.h"

namespace DFATransitionFactory {
    DFATransition create(DFANode* dfaNode, ASTNodeType prefix = AST_NULL_NODE);
}
#endif //JETLANG_DFA_TRANSITION_FACTORY_H

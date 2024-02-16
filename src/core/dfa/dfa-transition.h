//
// Created by Johny Georges on 2024-02-13.
//

#ifndef JETLANG_DFA_TRANSITION_H
#define JETLANG_DFA_TRANSITION_H

#include "../ast/types/ast-node-type.h"
#include "dfa-node.h"

struct DFATransition {
    ASTNodeType astNodeType;
    DFANode* destination;
};

#endif //JETLANG_DFA_TRANSITION_H

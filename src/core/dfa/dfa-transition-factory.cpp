//
// Created by Johny Georges on 2024-02-15.
//

#include "dfa-transition-factory.h"

namespace DFATransitionFactory {
    DFATransition create(DFANode* dfaNode) {
        return {
            dfaNode->getNodeType(),
            dfaNode
        };
    }
}
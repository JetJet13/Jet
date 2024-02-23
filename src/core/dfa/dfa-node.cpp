//
// Created by Johny Georges on 2024-02-13.
//

#include "dfa-node.h"

DFANode::DFANode(ASTNodeType astNodeType, bool start, bool end, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType) {
    _astNodeType = astNodeType;
    _start = start;
    _end = end;
    _targetAstNodeType = targetAstNodeType;
    _occurrence = occurrence;
    _transitions = std::vector<DFATransition>();
}

DFANode* DFANode::addTransition(DFATransition transition) {
    _transitions.push_back(transition);
    return this;
}

std::optional<DFANode*> DFANode::transition(ASTNodeType astNodeType) {
    if (this->isEnd()) {
        return {};
    } else if (_astNodeType == astNodeType &&
              (_occurrence == DFA_OCCURRENCE_ONCE_OR_MORE ||
               _occurrence == DFA_OCCURRENCE_NIL_OR_MORE)
    ) {
        return this;
    } else if (_astNodeType == astNodeType) {
        return {};
    }

    for (auto transition : _transitions) {
        if (transition.astNodeType == astNodeType) {
            return transition.destination;
        }
    }
    return {};
}

bool DFANode::isStart() {
    return this->_start;
}

bool DFANode::isEnd() {
    return this->_end;
}

ASTNodeType DFANode::getNodeType() {
    return this->_astNodeType;
}

std::optional<ASTNodeType> DFANode::getTargetAstNodeType() {
    return this->_targetAstNodeType;
}
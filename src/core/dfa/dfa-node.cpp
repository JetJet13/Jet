//
// Created by Johny Georges on 2024-02-13.
//

#include "dfa-node.h"

DFANode::DFANode(ASTNodeType astNodeType, bool start, bool end, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType) {
    _astNodeType = astNodeType;
    _start = start;
    _end = end;
    _prefixes = std::vector<ASTNodeType>();
    _targetAstNodeType = targetAstNodeType;
    _occurrence = occurrence;
    _transitions = std::vector<DFATransition>();
}

DFANode* DFANode::addPrefix(ASTNodeType astNodeType) {
    _prefixes.push_back(astNodeType);
    return this;
}

DFANode* DFANode::addTransition(DFATransition transition) {
    _transitions.push_back(transition);
    return this;
}

std::optional<DFANode*> DFANode::transition(ASTNodeType astNodeType, ASTNodeType prefix) {
    if (_astNodeType == astNodeType &&
              (_occurrence == DFA_OCCURRENCE_ONCE_OR_MORE ||
               _occurrence == DFA_OCCURRENCE_NIL_OR_MORE)
    ) {
        return this;
    } else if (this->isEnd() || _astNodeType == astNodeType) {
        return {};
    }

    for (auto transition : _transitions) {
        if (transition.astNodeType == astNodeType && transition.prefix == prefix) {
            return transition.destination;
        }
    }
    return {};
}

bool DFANode::canTransition(ASTNodeType astNodeType) {
    auto transitionResult = this->transition(astNodeType);
    if (transitionResult) {
        return true;
    }
    return false;
}

bool DFANode::isStart() {
    return this->_start;
}

bool DFANode::isEnd() {
    return this->_end;
}

bool DFANode::hasPrefix(ASTNodeType astNodeType) {
    return std::find(_prefixes.begin(), _prefixes.end(), astNodeType) != _prefixes.end();
}

ASTNodeType DFANode::getNodeType() {
    return this->_astNodeType;
}

std::optional<ASTNodeType> DFANode::getTargetAstNodeType() {
    return this->_targetAstNodeType;
}
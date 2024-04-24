//
// Created by Johny Georges on 2024-02-13.
//

#include "dfa.h"
#include "../../shared/utils/logger/logger.h"

DFA::DFA() {
    _startNodes = std::unordered_map<ASTNodeType, DFANode*, std::hash<int>>();
    _start = {};
    _current = {};
}

void DFA::init(ASTNodeType astNodeType) {
    auto startNode = _startNodes.find(astNodeType);
    if (startNode == _startNodes.end()) {
        throw std::invalid_argument( "no start DFA Node found for ASTNodeType");
    }

    _start = startNode->second;
    _current = startNode->second;
}

DFA* DFA::insertStartNode(ASTNodeType astNodeType, DFANode* dfaNode) {
    _startNodes.insert(std::pair<ASTNodeType, DFANode*>(astNodeType, dfaNode));
    return this;
}

DFA* DFA::insertStartNode(DFANode* dfaNode) {
    _startNodes.insert(std::pair<ASTNodeType, DFANode*>(dfaNode->getNodeType(), dfaNode));
    return this;
}

void DFA::reset() {
    _start = {};
    _current = {};
}

void DFA::determine(ASTNodeType astNodeType, ASTNodeType nextAstNodeType) {
    if (!_current) {
        return;
    }

    auto normalTransition = _current.value()->transition(astNodeType, nextAstNodeType);
    if (normalTransition) {
        _current = normalTransition;
        return;
    }

    for (auto nilTransitionNode : _current.value()->findNilTransitions()) {
        Logger::log("nilTransitionNode", nilTransitionNode->getNodeType());
        auto nilTransitionResult = nilTransitionNode->transition(nilTransitionNode->getNodeType(), nextAstNodeType);
        if (nilTransitionResult) {
            _current = nilTransitionResult;
            return;
        }

    }
    _current = {};
}

std::optional<DFANode*> DFA::getStartState() {
    return _start;
}

std::optional<DFANode*> DFA::getCurrentState() {
    return _current;
}

std::optional<DFANode*> DFA::findStartNode(ASTNodeType nodeType) {
    auto prefixNode = _startNodes.find(nodeType);
    if (prefixNode == _startNodes.end()) {
        return {};
    }
    return prefixNode->second;
}
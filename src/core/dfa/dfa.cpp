//
// Created by Johny Georges on 2024-02-13.
//

#include <MacTypes.h>
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

void DFA::reset() {
    _start = {};
    _current = {};
}

void DFA::determine(ASTNodeType astNodeType, ASTNodeType prefix) {
    if (!_current) {
        return;
    }

    _current = _current.value()->transition(astNodeType, prefix);
}

std::optional<DFANode*> DFA::getStartState() {
    return _start;
}

std::optional<DFANode*> DFA::getCurrentState() {
    return _current;
}

bool DFA::isValidPrefixForNode(ASTNodeType nodeType, ASTNodeType prefixNodeType) {
    auto prefixNode = _startNodes.find(nodeType);
    if (prefixNode == _startNodes.end()) {
        return false;
    }
    return prefixNode->second->hasPrefix(prefixNodeType);
}

bool DFA::isValidSuffixForNode(ASTNodeType nodeType, ASTNodeType suffixNodeType) {
    auto suffixNode = _startNodes.find(nodeType);
    if (suffixNode == _startNodes.end()) {
        return false;
    }
    return suffixNode->second->hasSuffix(suffixNodeType);
}
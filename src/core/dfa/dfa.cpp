//
// Created by Johny Georges on 2024-02-13.
//

#include "dfa.h"
#include "../../shared/utils/logger/logger.h"

DFA::DFA() {
    _startNodes = std::unordered_map<ASTNodeType, std::shared_ptr<DFANode>>();
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

DFA* DFA::insertStartNode(std::shared_ptr<DFANode> dfaNode) {
    _startNodes.insert(std::pair<ASTNodeType, std::shared_ptr<DFANode>>(dfaNode->getNodeType(), dfaNode));
    return this;
}

void DFA::reset() {
    _start = {};
    _current = {};
}

void DFA::determine(ASTNodeType nextAstNodeType) {
    if (!_current) {
        return;
    }

    _current = _current.value()->transition(nextAstNodeType);
}

std::optional<std::shared_ptr<DFANode>> DFA::getStartState() {
    return _start;
}

std::optional<std::shared_ptr<DFANode>> DFA::getCurrentState() {
    return _current;
}

std::optional<std::shared_ptr<DFANode>> DFA::findStartNode(ASTNodeType nodeType) {
    auto prefixNode = _startNodes.find(nodeType);
    if (prefixNode == _startNodes.end()) {
        return {};
    }
    return prefixNode->second;
}
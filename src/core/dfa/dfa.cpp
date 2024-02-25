//
// Created by Johny Georges on 2024-02-13.
//

#include <MacTypes.h>
#include "dfa.h"
#include "../../shared/utils/logger/logger.h"

DFA::DFA() {
    _startNodes = std::unordered_map<ASTNodeType, DFANode*, std::hash<int>>();
    _current = {};
}

void DFA::init(ASTNodeType astNodeType) {
//    Logger::log("DFA::init - ast node type", astNodeType);
    auto startNode = _startNodes.find(astNodeType);
    if (startNode == _startNodes.end()) {
        throw std::invalid_argument( "no start DFA Node found for ASTNodeType");
    }
    _current = startNode->second;
}

DFA* DFA::insertStartNode(ASTNodeType astNodeType, DFANode* dfaNode) {
    _startNodes.insert(std::pair<ASTNodeType, DFANode*>(astNodeType, dfaNode));
    return this;
}

void DFA::reset() {
    _current = {};
}

void DFA::determine(ASTNodeType astNodeType) {
    if (!_current) {
        return;
    }

    _current = _current.value()->transition(astNodeType);
    return;
}

std::optional<DFANode*> DFA::getCurrentState() {
    return _current;
}


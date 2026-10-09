// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-02-13.
//

#include "dfa-node.h"
#include "../../shared/utils/logger/logger.h"
#include <stack>

DFANode::DFANode(ASTNodeType astNodeType, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType) {
    _astNodeType = astNodeType;
    _predecessorsToBacktrackTo = std::vector<ASTNodeType>();
    _backtrackToPredecessorRules = std::vector<std::shared_ptr<BacktrackToPredecessorRule>>();
    _successorsToReduceSelfFor = std::vector<ASTNodeType>();
    _reduceToTargetMapsForPrevNode = std::vector<std::shared_ptr<ReduceToTargetMap>>();
    _reduceToTargetMapsForNextNode = std::vector<std::shared_ptr<ReduceToTargetMap>>();
    _reduceToTargetMapsForPrevNodeAndNextNode = std::vector<std::shared_ptr<ReduceToTargetDualMap>>();
    _targetAstNodeType = targetAstNodeType;
    _occurrence = occurrence;
    _transitions = std::vector<DFATransition>();
    _alwaysReduceSelf = false;
}

std::shared_ptr<DFANode> DFANode::backtrackWhenLastReducedNodeIsOneOf(std::vector<ASTNodeType> predecessors) {
    _predecessorsToBacktrackTo = std::move(predecessors);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::addBacktrackToPredecessorRule(std::shared_ptr<BacktrackToPredecessorRule> backtrackToPredecessorRule) {
    _backtrackToPredecessorRules.push_back(backtrackToPredecessorRule);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::addReduceToTargetMapForPrevNode(std::shared_ptr<ReduceToTargetMap> reduceToTargetMap) {
    _reduceToTargetMapsForPrevNode.push_back(reduceToTargetMap);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::addReduceToTargetMapForNextNode(std::shared_ptr<ReduceToTargetMap> reduceToTargetMap) {
    _reduceToTargetMapsForNextNode.push_back(reduceToTargetMap);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::addReduceToTargetMapForPrevNodeAndNextNode(std::shared_ptr<ReduceToTargetDualMap> reduceToTargetDualMap) {
    _reduceToTargetMapsForPrevNodeAndNextNode.push_back(reduceToTargetDualMap);
    return shared_from_this();
}


std::shared_ptr<DFANode> DFANode::reduceSelfWhenNextNodeIsOneOf(std::vector<ASTNodeType> successors) {
    _successorsToReduceSelfFor = std::move(successors);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::addTransition(DFATransition transition) {
    _transitions.push_back(transition);
    return shared_from_this();
}

std::shared_ptr<DFANode> DFANode::markAlwaysReduceSelf() {
    _alwaysReduceSelf = true;
    return shared_from_this();
}

std::optional<std::shared_ptr<DFANode>> DFANode::transition(ASTNodeType nextAstNodeType) {
    if (_astNodeType == nextAstNodeType &&
        (_occurrence == DFA_OCCURRENCE_ONCE_OR_MORE ||
               _occurrence == DFA_OCCURRENCE_NIL_OR_MORE)
    ) {
        return shared_from_this();
    }

    for (auto transition : _transitions) {
        if (transition.astNodeType == nextAstNodeType) {
            return transition.destination;
        }
        if (transition.astNodeType == AST_ANY_NODE) {

            return transition.destination;
        }
    }

    auto result = std::optional<std::shared_ptr<DFANode>>();
    for (auto transition : _transitions) {
        if (transition.destination->isNilOrMore() || transition.destination->isNilOrOnce()) {
            result = transition.destination->transition(nextAstNodeType);
        }
    }
    return result;
}

bool DFANode::shouldBacktrackTo(ASTNodeType astNodeType) {
    return std::find(_predecessorsToBacktrackTo.begin(), _predecessorsToBacktrackTo.end(), astNodeType) != _predecessorsToBacktrackTo.end();
}

bool DFANode::shouldBacktrackWhenPrevNodeAndNextNodeAre(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType) {
    for (auto backtrackToPredecessorRule: _backtrackToPredecessorRules) {
        if (backtrackToPredecessorRule->match(prevAstNodeType, nextAstNodeType)) {
            return true;
        }
    }
    return false;
}

bool DFANode::shouldReduceSelfFor(ASTNodeType astNodeType) {
    return std::find(_successorsToReduceSelfFor.begin(), _successorsToReduceSelfFor.end(), astNodeType) != _successorsToReduceSelfFor.end();
}

bool DFANode::shouldReduceToTargetWhenPrevNodeIs(ASTNodeType astNodeType) {
    for (auto reduceToTargetMap: _reduceToTargetMapsForPrevNode) {
        if (reduceToTargetMap->isNodeTypeInMap(astNodeType)) {
            return true;
        }
    }
    return false;
}

bool DFANode::shouldReduceToTargetWhenNextNodeIs(ASTNodeType astNodeType) {
    for (auto reduceToTargetMap: _reduceToTargetMapsForNextNode) {
        if (reduceToTargetMap->isNodeTypeInMap(astNodeType)) {
            return true;
        }
    }
    return false;
}

bool DFANode::shouldReduceToTargetWhenPrevNodeAndNextNodeIs(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType) {
    for (auto reduceToTargetMap: _reduceToTargetMapsForPrevNodeAndNextNode) {
        if (reduceToTargetMap->isNodeTypeInMap(prevAstNodeType, nextAstNodeType)) {
            return true;
        }
    }
    return false;
}

std::optional<ASTNodeType> DFANode::getReduceTargetForPrevNode(ASTNodeType astNodeType) {
    for (auto reduceToTargetMap: _reduceToTargetMapsForPrevNode) {
        if (reduceToTargetMap->isNodeTypeInMap(astNodeType)) {
            return reduceToTargetMap->getTarget();
        }
    }
    return {};
}


std::optional<ASTNodeType> DFANode::getReduceTargetForNextNode(ASTNodeType astNodeType) {
    for (auto reduceToTargetMap: _reduceToTargetMapsForNextNode) {
        if (reduceToTargetMap->isNodeTypeInMap(astNodeType)) {
            return reduceToTargetMap->getTarget();
        }
    }
    return {};
}

std::optional<ASTNodeType> DFANode::getReduceTargetForPrevNodeAndNextNode(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType) {
    for (auto reduceToTargetDualMap: _reduceToTargetMapsForPrevNodeAndNextNode) {
        if (reduceToTargetDualMap->isNodeTypeInMap(prevAstNodeType, nextAstNodeType)) {
            return reduceToTargetDualMap->getTarget();
        }
    }
    return {};
}

bool DFANode::alwaysReduceSelf() {
    return _alwaysReduceSelf;
}

bool DFANode::isNilOrMore() {
    return _occurrence == DFA_OCCURRENCE_NIL_OR_MORE;
}

bool DFANode::isNilOrOnce() {
    return _occurrence == DFA_OCCURRENCE_NIL_OR_ONCE;
}

bool DFANode::isOnceOrMore() {
    return _occurrence == DFA_OCCURRENCE_ONCE_OR_MORE;
}

bool DFANode::isOnce() {
    return _occurrence == DFA_OCCURRENCE_ONCE;
}

bool DFANode::isAnyNode() {
    return _astNodeType == AST_ANY_NODE;
}

ASTNodeType DFANode::getNodeType() {
    return _astNodeType;
}

std::optional<ASTNodeType> DFANode::getTargetAstNodeType() {
    return _targetAstNodeType.value();
}

bool DFANode::hasTargetAstNodeType() {
    return _targetAstNodeType.has_value();
}
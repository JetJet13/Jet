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

#ifndef JETLANG_DFA_NODE_H
#define JETLANG_DFA_NODE_H

#include <vector>
#include <optional>
#include "../ast/types/ast-node-type.h"
#include "types/dfa-node-occurrence.h"
#include "types/reduce-to-target-map.h"
#include "types/reduce-to-target-dual-map.h"
#include "types/backtrack-to-predecessor-rule.h"

struct DFATransition;

class DFANode : public std::enable_shared_from_this<DFANode> {
private:
    std::vector<ASTNodeType> _predecessorsToBacktrackTo;
    std::vector<std::shared_ptr<BacktrackToPredecessorRule>> _backtrackToPredecessorRules;
    std::vector<ASTNodeType> _successorsToReduceSelfFor;
    std::optional<ASTNodeType> _targetAstNodeType;
    std::vector<std::shared_ptr<ReduceToTargetMap>> _reduceToTargetMapsForPrevNode;
    std::vector<std::shared_ptr<ReduceToTargetMap>> _reduceToTargetMapsForNextNode;
    std::vector<std::shared_ptr<ReduceToTargetDualMap>> _reduceToTargetMapsForPrevNodeAndNextNode;
    DFANodeOccurrence _occurrence;
    ASTNodeType _astNodeType;
    std::vector<DFATransition> _transitions;
    bool _alwaysReduceSelf;
public:
    DFANode(ASTNodeType astNodeType, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType = {});
    std::shared_ptr<DFANode> backtrackWhenLastReducedNodeIsOneOf(std::vector<ASTNodeType> predecessors);
    std::shared_ptr<DFANode> addBacktrackToPredecessorRule(std::shared_ptr<BacktrackToPredecessorRule> backtrackToPredecessorRule);
    std::shared_ptr<DFANode> addReduceToTargetMapForPrevNode(std::shared_ptr<ReduceToTargetMap> reduceToTargetMap);
    std::shared_ptr<DFANode> addReduceToTargetMapForNextNode(std::shared_ptr<ReduceToTargetMap> reduceToTargetMap);
    std::shared_ptr<DFANode> addReduceToTargetMapForPrevNodeAndNextNode(std::shared_ptr<ReduceToTargetDualMap> reduceToTargetDualMap);
    std::shared_ptr<DFANode> reduceSelfWhenNextNodeIsOneOf(std::vector<ASTNodeType> successors);
    std::shared_ptr<DFANode> addTransition(DFATransition transition);
    std::shared_ptr<DFANode> markAlwaysReduceSelf();
    std::optional<std::shared_ptr<DFANode>> transition(ASTNodeType nextAstNodeType);
    bool shouldBacktrackTo(ASTNodeType astNodeType);
    bool shouldBacktrackWhenPrevNodeAndNextNodeAre(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType);
    bool shouldReduceSelfFor(ASTNodeType astNodeType);
    bool shouldReduceToTargetWhenPrevNodeIs(ASTNodeType astNodeType);
    bool shouldReduceToTargetWhenNextNodeIs(ASTNodeType astNodeType);
    bool shouldReduceToTargetWhenPrevNodeAndNextNodeIs(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType);
    bool alwaysReduceSelf();
    bool isNilOrMore();
    bool isNilOrOnce();
    bool isOnceOrMore();
    bool isOnce();
    bool isAnyNode();
    ASTNodeType getNodeType();
    std::optional<ASTNodeType> getReduceTargetForPrevNode(ASTNodeType astNodeType);
    std::optional<ASTNodeType> getReduceTargetForNextNode(ASTNodeType astNodeType);
    std::optional<ASTNodeType> getReduceTargetForPrevNodeAndNextNode(ASTNodeType prevAstNodeType, ASTNodeType nextAstNodeType);
    std::optional<ASTNodeType> getTargetAstNodeType();
    bool hasTargetAstNodeType();
};

struct DFATransition {
    ASTNodeType astNodeType;
    std::shared_ptr<DFANode> destination;
};

#endif //JETLANG_DFA_NODE_H

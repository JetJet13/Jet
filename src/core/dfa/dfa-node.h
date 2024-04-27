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

struct DFATransition;

class DFANode {
private:
    std::vector<ASTNodeType> _predecessorsToBacktrackTo;
    std::vector<ASTNodeType> _successorsToReduceSelfFor;
    std::optional<ASTNodeType> _targetAstNodeType;
    std::vector<ReduceToTargetMap*> _reduceToTargetMapsForPrevNode;
    std::vector<ReduceToTargetMap*> _reduceToTargetMapsForNextNode;
    std::vector<ReduceToTargetDualMap*> _reduceToTargetMapsForPrevNodeAndNextNode;
    DFANodeOccurrence _occurrence;
    ASTNodeType _astNodeType;
    std::vector<DFATransition> _transitions;
    bool _alwaysReduceSelf;
public:
    DFANode(ASTNodeType astNodeType, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType = {});
    DFANode* backtrackWhenLastReducedNodeIsOneOf(std::vector<ASTNodeType> predecessors);
    DFANode* addReduceToTargetMapForPrevNode(ReduceToTargetMap* reduceToTargetMap);
    DFANode* addReduceToTargetMapForNextNode(ReduceToTargetMap* reduceToTargetMap);
    DFANode* addReduceToTargetMapForPrevNodeAndNextNode(ReduceToTargetDualMap* reduceToTargetDualMap);
    DFANode* reduceSelfWhenNextNodeIsOneOf(std::vector<ASTNodeType> successors);
    DFANode* addTransition(DFATransition transition);
    DFANode* markAlwaysReduceSelf();
    std::optional<DFANode*> transition(ASTNodeType nextAstNodeType);
    std::vector<DFANode*> findNilTransitions();
    bool shouldBacktrackTo(ASTNodeType astNodeType);
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
    DFANode* destination;
};

#endif //JETLANG_DFA_NODE_H

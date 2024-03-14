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

struct DFATransition;

class DFANode {
private:
    std::vector<ASTNodeType> _predecessorsToBacktrackTo;
    std::vector<ASTNodeType> _successorsToReduceSelfFor;
    std::optional<ASTNodeType> _targetAstNodeType;
    std::optional<ASTNodeType> _reduceToTargetWhenOnlyNode;
    std::vector<ReduceToTargetMap*> _reduceToTargetMaps;
    DFANodeOccurrence _occurrence;
    ASTNodeType _astNodeType;
    std::vector<DFATransition> _transitions;
    bool _alwaysReduceSelf;
public:
    DFANode(ASTNodeType astNodeType, DFANodeOccurrence occurrence, std::optional<ASTNodeType> targetAstNodeType = {});
    DFANode* backtrackWhenLastReducedNodeIsOneOf(std::vector<ASTNodeType> predecessors);
    DFANode* addReduceToTargetMap(ReduceToTargetMap* reduceToTargetMap);
    DFANode* reduceSelfWhenNextNodeIsOneOf(std::vector<ASTNodeType> successors);
    DFANode* addTransition(DFATransition transition);
    DFANode* markAlwaysReduceSelf();
    DFANode* setReduceToTargetWhenOnlyNode(ASTNodeType astNodeType);
    std::optional<DFANode*> transition(ASTNodeType astNodeType);
    bool shouldBacktrackTo(ASTNodeType astNodeType);
    bool shouldReduceSelfFor(ASTNodeType astNodeType);
    bool shouldReduceToTargetFor(ASTNodeType astNodeType);
    bool shouldReduceToTargetWhenOnlyNode();
    bool alwaysReduceSelf();
    ASTNodeType getNodeType();
    std::optional<ASTNodeType> getReduceTargetFor(ASTNodeType astNodeType);
    std::optional<ASTNodeType> getTargetAstNodeType();
    std::optional<ASTNodeType> getReduceTargetWhenOnlyNode();
    bool hasTargetAstNodeType();
};

struct DFATransition {
    ASTNodeType astNodeType;
    DFANode* destination;
};

#endif //JETLANG_DFA_NODE_H

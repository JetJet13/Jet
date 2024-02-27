//
// Created by Johny Georges on 2024-02-13.
//

#ifndef JETLANG_DFA_NODE_H
#define JETLANG_DFA_NODE_H

#include <vector>
#include <optional>
#include "../ast/types/ast-node-type.h"
#include "types/dfa-node-occurrence.h"

struct DFATransition;

class DFANode {
private:
    bool _start;
    bool _end;
    std::vector<ASTNodeType> _prefixes;
    std::optional<ASTNodeType> _targetAstNodeType;
    DFANodeOccurrence _occurrence;
    ASTNodeType _astNodeType;
    std::vector<DFATransition> _transitions;
public:
    DFANode(ASTNodeType astNodeType, bool start, bool end, DFANodeOccurrence occurrence, std::optional<ASTNodeType> _targetAstNodeType = {});
    DFANode* addPrefix(ASTNodeType astNodeType);
    DFANode* addTransition(DFATransition transition);
    std::optional<DFANode*> transition(ASTNodeType astNodeType, ASTNodeType prefix = AST_NULL_NODE);
    bool canTransition(ASTNodeType astNodeType);
    bool isStart();
    bool isEnd();
    bool isPrefix(ASTNodeType astNodeType);
    ASTNodeType getNodeType();
    bool isTerminatorNode();
    std::optional<ASTNodeType> getTargetAstNodeType();
};

struct DFATransition {
    ASTNodeType prefix;
    ASTNodeType astNodeType;
    DFANode* destination;
};

#endif //JETLANG_DFA_NODE_H

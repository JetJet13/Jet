//
// Created by Johny Georges on 2024-02-13.
//

#ifndef JETLANG_DFA_H
#define JETLANG_DFA_H

#include <unordered_map>
#include "../ast/ast-nodes/ast-node.h"
#include "dfa.h"
#include "dfa-node.h"

class DFA {
private:
    std::unordered_map<ASTNodeType, DFANode*, std::hash<int>> _startNodes;
    std::optional<DFANode*> _start;
    std::optional<DFANode*> _current;
public:
    DFA();
    void init(ASTNodeType astNodeType);
    DFA* insertStartNode(ASTNodeType astNodeType, DFANode* dfaNode);
    DFA* insertStartNode(DFANode* dfaNode);
    void reset();
    void determine(ASTNodeType astNodeType);
    std::optional<DFANode*> getStartState();
    std::optional<DFANode*> getCurrentState();
    std::optional<DFANode*> findStartNode(ASTNodeType nodeType);
    bool isValidPredecessorForNode(ASTNodeType nodeType, ASTNodeType prefixNodeType);
    bool isValidSuccessorForNode(ASTNodeType nodeType, ASTNodeType suffixNodeType);
};
#endif //JETLANG_DFA_H

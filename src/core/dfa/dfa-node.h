//
// Created by Johny Georges on 2024-02-13.
//

#ifndef JETLANG_DFA_NODE_H
#define JETLANG_DFA_NODE_H

#include <vector>
#include <optional>
#include "../ast/types/ast-node-type.h"
#include "dfa-transition.h"
#include "types/dfa-node-occurrence.h"

class DFANode {
private:
    bool _start;
    bool _end;
    DFANodeOccurrence _occurrence;
    ASTNodeType _astNodeType;
    std::vector<DFATransition> _transitions;
public:
    DFANode(ASTNodeType astNodeType, bool start, bool end, DFANodeOccurrence occurrence);
    DFANode* addTransition(DFATransition transition);
    std::optional<DFANode*> transition(ASTNodeType astNodeType);
    bool isStart();
    bool isEnd();
    ASTNodeType getNodeType();
};

#endif //JETLANG_DFA_NODE_H

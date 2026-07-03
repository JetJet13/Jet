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
    std::unordered_map<ASTNodeType, std::shared_ptr<DFANode>> _startNodes;
    std::optional<std::shared_ptr<DFANode>> _start;
    std::optional<std::shared_ptr<DFANode>> _current;
public:
    DFA();
    void init(ASTNodeType astNodeType);
    DFA* insertStartNode(std::shared_ptr<DFANode> dfaNode);
    void reset();
    void determine(ASTNodeType nextAstNodeType);
    std::optional<std::shared_ptr<DFANode>> getStartState();
    std::optional<std::shared_ptr<DFANode>> getCurrentState();
    std::optional<std::shared_ptr<DFANode>> findStartNode(ASTNodeType nodeType);
};
#endif //JETLANG_DFA_H

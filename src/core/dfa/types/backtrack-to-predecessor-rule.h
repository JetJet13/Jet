//
// Created by Johny Georges on 2026-01-28.
//

#ifndef JETLANG_BACKTRACK_TO_PREDECESSOR_RULE_H
#define JETLANG_BACKTRACK_TO_PREDECESSOR_RULE_H

#include <vector>
#include "../../ast/types/ast-node-type.h"

class BacktrackToPredecessorRule {
private:
    ASTNodeType _predecessor;
    ASTNodeType _successor;
public:
    BacktrackToPredecessorRule(ASTNodeType predecessor, ASTNodeType successor);
    bool match(ASTNodeType predecessor, ASTNodeType successor);
};

#endif //JETLANG_BACKTRACK_TO_PREDECESSOR_RULE_H

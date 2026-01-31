//
// Created by Johny Georges on 2026-01-28.
//

#include "backtrack-to-predecessor-rule.h"

BacktrackToPredecessorRule::BacktrackToPredecessorRule(ASTNodeType predecessor, ASTNodeType successor) {
    _predecessor = predecessor;
    _successor = successor;
}

bool BacktrackToPredecessorRule::match(ASTNodeType prevNodeType, ASTNodeType nextNodeType) {
    return _predecessor == prevNodeType && _successor == nextNodeType;
}
//
// Created by Johny Georges on 2024-05-10.
//

#include "ast-traverser.h"


ASTTraverser::ASTTraverser() {
    _stack = std::stack<ASTNode*>();
    _startNode = {};
    _hasMore = false;
}

void ASTTraverser::start(ASTNode* node) {
    _startNode = node;
}

void ASTTraverser::reset() {
    _startNode = {};
    _hasMore = false;
}

std::optional<ASTNode*> ASTTraverser::next() {
    return {};
}

bool ASTTraverser::hasMore() {
    return _hasMore;
}
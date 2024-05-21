//
// Created by Johny Georges on 2024-05-10.
//

#include "ast-traverser.h"

ASTTraverser::ASTTraverser() {
    _stack = std::stack<ASTNode*>();
    _hasMore = false;
}

void ASTTraverser::init(ASTNode* startNode) {
    this->reset();
    _stack.push(startNode);
}

void ASTTraverser::reset() {
    _stack = std::stack<ASTNode*>();
    _hasMore = false;
}

std::optional<ASTNode*> ASTTraverser::next() {
    if (_stack.empty()) {
        _hasMore = false;
        return {};
    }
    if (!_stack.empty()) {
        auto node = _stack.top();
        _stack.pop();
        for (auto child : node->getChildren()) {
            _stack.push(child);
        }
        return node;
    }
    return {};
}

bool ASTTraverser::hasMore() {
    return _hasMore;
}
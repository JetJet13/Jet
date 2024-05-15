//
// Created by Johny Georges on 2024-05-10.
//

#include "ast-traverser.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTraverser::ASTTraverser() {
    _stack = std::stack<ASTNode*>();
    _traverseStack = std::stack<ASTNode*>();
    _hasMore = false;
}

void ASTTraverser::init(ASTNode* startNode) {
    this->reset();
    _traverseStack.push(startNode);
    _stack.push(startNode);
    while (!_stack.empty()) {
        auto node = _stack.top();
        _stack.pop();
        for (auto child : node->getChildren()) {
            _stack.push(child);
            _traverseStack.push(child);
        }

    }
}

void ASTTraverser::reset() {
    _stack = std::stack<ASTNode*>();
    _traverseStack = std::stack<ASTNode*>();
    _hasMore = false;
}

std::optional<ASTNode*> ASTTraverser::next() {
    if (_traverseStack.empty()) {
        Logger::log("_traverseStack is empty");
        _hasMore = false;
        return {};
    }
    auto node = _traverseStack.top();
    _traverseStack.pop();
    return node;
}

bool ASTTraverser::hasMore() {
    return _hasMore;
}
//
// Created by Johny Georges on 2024-05-10.
//

#include "ast-traverser.h"
#include "../ast/ast-nodes/ast-terminator-node.h"

ASTTraverser::ASTTraverser() {
    _stack = std::stack<std::shared_ptr<ASTNode>>();
    _hasMore = false;
    _insertTerminatorNodeAfterNext = false;
}

void ASTTraverser::init(std::shared_ptr<ASTNode> startNode) {
    this->reset();
    _stack.push(startNode);
    _hasMore = true;
}

void ASTTraverser::reset() {
    _stack = std::stack<std::shared_ptr<ASTNode>>();
    _hasMore = false;
}

void ASTTraverser::insertTerminatorNodeAfterNext() {
    _insertTerminatorNodeAfterNext = true;
}

std::optional<std::shared_ptr<ASTNode>> ASTTraverser::next() {
    if (_stack.empty()) {
        _hasMore = false;
        return {};
    }

    if (_insertTerminatorNodeAfterNext) {
        auto nextNode = _stack.top();
        _stack.pop();
        _stack.push(std::make_shared<ASTTerminatorNode>(nullptr));
        _stack.push(nextNode);
        _insertTerminatorNodeAfterNext = false;
    }

    auto node = _stack.top();
    _stack.pop();
    auto children = node->getChildren();
    std::reverse(children.begin(), children.end());
    for (auto child : children) {
        _stack.push(child);
    }
    return node;
}

std::optional<std::shared_ptr<ASTNode>> ASTTraverser::peek() {
    if (_stack.empty()) {
        return {};
    }
    return _stack.top();
}

bool ASTTraverser::hasMore() {
    return _hasMore;
}
//
// Created by Johny Georges on 2024-02-10.
//

#include "handle.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

Handle::Handle() {
    _handle = std::deque<ASTNode*>();
}

std::optional<ASTNode*> Handle::at(int index) {
    if (_handle.size() < (index + 1) || index < 0) {
        return {};
    }
    return _handle[index];
}

bool Handle::isNodeTypeAt(int index, ASTNodeType astNodeType) {
    auto node = this->at(index);
    if (node) {
        return node.value()->getNodeType() == astNodeType;
    }
    return false;
}

bool Handle::isEmpty() {
    return _handle.empty();
}

void Handle::clear() {
    _handle.clear();
}

int Handle::size() {
    return _handle.size();
}

std::vector<ASTNode*> Handle::getFirstNodes(int numNodesToGet) {
    auto firstNodes = std::vector<ASTNode*>();
    if (numNodesToGet <= 0) {
        return firstNodes;
    }

    if (numNodesToGet > _handle.size()) {
        throw std::invalid_argument("numNodesToGet too large.");
    }

    for (int i = 0; i < numNodesToGet; ++i) {
        firstNodes.push_back(_handle[i]);
    }

    return firstNodes;
}

void Handle::removeFirstNodes(int numNodesToRemove) {
    _handle.erase(_handle.begin(), _handle.begin() + numNodesToRemove);
}

void Handle::push(ASTNode* node) {
    _handle.push_front(node);
}
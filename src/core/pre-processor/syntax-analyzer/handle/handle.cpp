//
// Created by Johny Georges on 2024-02-10.
//

#include "handle.h"
#include "../../../../shared/utils/logger/logger.h"

Handle::Handle() {
    _handle = std::deque<ASTNode*>();
    _lastReducedNode = {};
    _peekNode = {};
}

std::optional<ASTNode*> Handle::at(int index) {
    if (_handle.size() < (index + 1) || index < 0) {
        return {};
    }
    return _handle[index];
}

std::optional<ASTNode*> Handle::first() {
    if (this->isEmpty()) {
        return {};
    }

    return _handle[0];
}


std::optional<ASTNode*> Handle::last() {
    if (this->isEmpty()) {
        return {};
    }

    return _handle[_handle.size() - 1];
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

bool Handle::isTerminatorMode() {
    return !this->isEmpty() && this->last().value()->is(AST_TERMINATOR_NODE);
}

bool Handle::isTerminatorOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_TERMINATOR_NODE);
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

void Handle::append(ASTNode* node) {
    _handle.push_back(node);
}

void Handle::prepend(ASTNode* node) {
    _handle.push_front(node);
}

std::optional<ASTNode*> Handle::getLastReducedNode() {
    return _lastReducedNode;
}

void Handle::setLastReducedNode(std::optional<ASTNode*> lastReducedNode) {
    _lastReducedNode = lastReducedNode;
}

void Handle::clearLastReducedNode() {
    _lastReducedNode = {};
}

std::optional<ASTNode*> Handle::getPeekNode() {
    return _peekNode;
}

void Handle::setPeekNode(std::optional<ASTNode*> peekNode) {
    _peekNode = peekNode;
}

void Handle::clearPeekNode() {
    _peekNode = {};
}

void Handle::print() {
    if (this->isEmpty()) {
        Logger::log("-------- Handle --------");
        Logger::log("EMPTY");
        Logger::log("------------------------");
        return;
    }
    Logger::log("-------- Handle --------");
    for (auto node : _handle) {
        node->print();
    }
    Logger::log("------------------------");
}
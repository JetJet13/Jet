//
// Created by Johny Georges on 2024-02-10.
//

#include "handle.h"
#include "../../../../shared/utils/logger/logger.h"

Handle::Handle() {
    _handle = std::deque<ASTNode*>();
    _lastReducedNode = {};
    _peekNode = {};
    _mode = HANDLE_NORMAL_MODE;
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

HandleMode Handle::getMode() {
    return _mode;
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
    return _mode == HANDLE_TERMINATOR_MODE;
}

bool Handle::isTerminatorOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_TERMINATOR_NODE);
}

bool Handle::isGroupEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_GROUP_START_NODE) && this->last().value()->is(AST_GROUP_END_NODE);
}

bool Handle::isGroupingMode() {
    return _mode == HANDLE_GROUP_MODE;
}

bool Handle::isGroupingOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_GROUP_END_NODE);
}

bool Handle::isArrayEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_LEFT_BRACKET_NODE) && this->last().value()->is(AST_RIGHT_BRACKET_NODE);
}

bool Handle::isArrayMode() {
    return _mode == HANDLE_ARRAY_MODE;
}

bool Handle::isArrayOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_RIGHT_BRACKET_NODE);
}

bool Handle::isFunctionBlockOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_FUNCTION_BLOCK_NODE);
}

bool Handle::isStructEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_STRUCT_START_NODE) && this->last().value()->is(AST_STRUCT_END_NODE);
}

bool Handle::isStructMode() {
    return _mode == HANDLE_STRUCT_MODE;
}

bool Handle::isStructEndOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_STRUCT_END_NODE);
}

bool Handle::isFunctionParameterListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_FUNCTION_PARAMETER_LIST_START_NODE) && this->last().value()->is(AST_FUNCTION_PARAMETER_LIST_END_NODE);
}

bool Handle::isFunctionParameterListMode() {
    return _mode == HANDLE_FUNCTION_PARAMETER_LIST_MODE;
}

bool Handle::isFunctionParameterListEndOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_FUNCTION_PARAMETER_LIST_END_NODE);
}

bool Handle::isEnumKeyValueListOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_ENUM_KEY_VALUE_LIST_NODE);
}

bool Handle::isEnumKeyValueListEndOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_ENUM_KEY_VALUE_LIST_END_NODE);
}

bool Handle::isEnumKeyValueListEndMode(){
    return _mode == HANDLE_ENUM_KEY_VALUE_LIST_MODE;
}

bool Handle::isEnumKeyValueListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_ENUM_KEY_VALUE_LIST_START_NODE) && this->last().value()->is(AST_ENUM_KEY_VALUE_LIST_END_NODE);
}

bool Handle::isNormalMode() {
    return _mode == HANDLE_NORMAL_MODE;
}

bool Handle::isNotNormalMode() {
    return !this->isNormalMode();
}

void Handle::clear() {
    _handle.clear();
    this->determineMode();
}

unsigned long Handle::size() {
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
    this->determineMode();
}

void Handle::removeFirstNode() {
    _handle.pop_front();
    this->determineMode();
}

void Handle::removeLastNode() {
    _handle.pop_back();
    this->determineMode();
}

void Handle::append(ASTNode* node) {
    _handle.push_back(node);
    this->determineMode();
}

void Handle::prepend(ASTNode* node) {
    _handle.push_front(node);
    this->determineMode();
}

void Handle::replace(int index, ASTNode* newNode) {
    if (_handle.size() < (index + 1) || index < 0) {
        throw std::invalid_argument("invalid index value for replace operation");
    }
    _handle[index] = newNode;
    this->determineMode();
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

std::optional<ASTNode*> Handle::getPrevNodeFor(int index) {
    if (index == 0) {
        return this->getLastReducedNode();
    }

    return this->at(index - 1);
}

std::optional<ASTNode*> Handle::getNextNodeFor(int index) {
    if (index == _handle.size() - 1) {
        return this->getPeekNode();
    }
    return this->at(index + 1);
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

void Handle::determineMode() {
    if (!this->isEmpty() && this->last().value()->is(AST_TERMINATOR_NODE)) {
        _mode = HANDLE_TERMINATOR_MODE;
    } else if (!this->isEmpty() && this->last().value()->is(AST_RIGHT_BRACKET_NODE)) {
        _mode = HANDLE_ARRAY_MODE;
    } else if (!this->isEmpty() && this->last().value()->is(AST_GROUP_END_NODE)) {
        _mode = HANDLE_GROUP_MODE;
    } else if (!this->isEmpty() && this->last().value()->is(AST_STRUCT_END_NODE)) {
        _mode = HANDLE_STRUCT_MODE;
    }  else if (!this->isEmpty() && this->last().value()->is(AST_FUNCTION_BLOCK_NODE)) {
        _mode = HANDLE_FUNCTION_BLOCK_MODE;
    } else if (!this->isEmpty() && this->last().value()->is(AST_FUNCTION_PARAMETER_LIST_END_NODE)) {
        _mode = HANDLE_FUNCTION_PARAMETER_LIST_MODE;
    } else if (!this->isEmpty() && this->last().value()->isOneOf({ AST_ENUM_KEY_VALUE_LIST_NODE, AST_ENUM_KEY_VALUE_LIST_END_NODE })) {
        _mode = HANDLE_ENUM_KEY_VALUE_LIST_MODE;
    } else {
        _mode = HANDLE_NORMAL_MODE;
    }
}
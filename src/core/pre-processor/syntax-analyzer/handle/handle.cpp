// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-02-10.
//

#include "handle.h"
#include "../../../../shared/utils/logger/logger.h"

Handle::Handle() {
    _handle = std::deque<std::shared_ptr<ASTNode>>();
    _lastReducedNode = std::nullopt;
    _peekNode = std::nullopt;
}

std::optional<std::shared_ptr<ASTNode>> Handle::at(int index) {
    if (_handle.empty() || _handle.size() < (index + 1) || index < 0) {
        return std::nullopt;
    }
    return _handle[index];
}

std::optional<std::shared_ptr<ASTNode>> Handle::first() {
    if (this->isEmpty()) {
        return std::nullopt;
    }

    return _handle[0];
}


std::optional<std::shared_ptr<ASTNode>> Handle::last() {
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

bool Handle::isTerminatorOnlyNode() {
    return _handle.size() == 1 && this->isNodeTypeAt(0, AST_TERMINATOR_NODE);
}

bool Handle::isGroupEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_GROUP_START_NODE) && this->last().value()->is(AST_GROUP_END_NODE);
}

bool Handle::isArrayEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_LEFT_BRACKET_NODE) && this->last().value()->is(AST_RIGHT_BRACKET_NODE);
}

bool Handle::isStructEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_STRUCT_START_NODE) && this->last().value()->is(AST_STRUCT_END_NODE);
}

bool Handle::isStructTypeEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_STRUCT_TYPE_START_NODE) && this->last().value()->is(AST_STRUCT_TYPE_END_NODE);
}

bool Handle::isTupleTypeEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_TUPLE_TYPE_START_NODE) && this->last().value()->is(AST_TUPLE_TYPE_END_NODE);
}

bool Handle::isFunctionParameterListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_FUNCTION_PARAMETER_LIST_START_NODE) && this->last().value()->is(AST_FUNCTION_PARAMETER_LIST_END_NODE);
}

bool Handle::isFunctionArgumentListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_FUNCTION_ARGUMENT_LIST_START_NODE) && this->last().value()->is(AST_FUNCTION_ARGUMENT_LIST_END_NODE);
}


bool Handle::isEnumKeyValueListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_ENUM_KEY_VALUE_LIST_START_NODE) && this->last().value()->is(AST_ENUM_KEY_VALUE_LIST_END_NODE);
}

bool Handle::isInterfacePropertyListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_INTERFACE_START_NODE) && this->last().value()->is(AST_INTERFACE_END_NODE);
}

bool Handle::isImplementsInterfaceListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_IMPLEMENTS_NODE) &&
           this->last().value()->is(AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE);
}

bool Handle::isTupleListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_TUPLE_LIST_START_NODE) && this->last().value()->is(AST_TUPLE_LIST_END_NODE);
}

bool Handle::isModuleListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_MODULE_LIST_START_NODE) && this->last().value()->is(AST_MODULE_LIST_END_NODE);
}

bool Handle::isImportModuleListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_IMPORT_MODULE_LIST_START_NODE) && this->last().value()->is(AST_IMPORT_MODULE_LIST_END_NODE);
}

bool Handle::isLambdaTypeParameterListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE) && this->last().value()->is(AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE);
}

bool Handle::isTypeParameterListEnclosed() {
    if (_handle.size() < 2) {
        return false;
    }
    return this->first().value()->is(AST_TYPE_PARAMETER_LIST_START_NODE) && this->last().value()->is(AST_TYPE_PARAMETER_LIST_END_NODE);
}

bool Handle::hasOneAndOnlyNode() {
    return _handle.size() == 1 && !_peekNode.has_value();
}

void Handle::clear() {
    _handle.clear();
}

void Handle::reset() {
    _handle.clear();
    _peekNode = {};
    _lastReducedNode = {};
}

uint64_t Handle::size() {
    return _handle.size();
}

std::vector<std::shared_ptr<ASTNode>> Handle::getFirstNodes(int numNodesToGet) {
    auto firstNodes = std::vector<std::shared_ptr<ASTNode>>();
    if (numNodesToGet <= 0) {
        return firstNodes;
    }

    if (numNodesToGet > _handle.size()) {
        throw std::invalid_argument("numNodesToGet too large.");
    }

    for (uint64_t i = 0; i < numNodesToGet; ++i) {
        firstNodes.push_back(_handle[i]);
    }

    return firstNodes;
}

void Handle::removeFirstNodes(int numNodesToRemove) {
    _handle.erase(_handle.begin(), _handle.begin() + numNodesToRemove);
}

void Handle::removeFirstNode() {
    _handle.pop_front();
}

void Handle::removeLastNode() {
    _handle.pop_back();
}

void Handle::append(std::shared_ptr<ASTNode> node) {
    _handle.push_back(node);
}

void Handle::prepend(std::shared_ptr<ASTNode> node) {
    _handle.push_front(node);
}

void Handle::replace(int index, std::shared_ptr<ASTNode> newNode) {
    if (_handle.size() < (index + 1) || index < 0) {
        throw std::invalid_argument("invalid index value for replace operation");
    }
    _handle[index] = newNode;
}

std::optional<std::shared_ptr<ASTNode>> Handle::getLastReducedNode() {
    return _lastReducedNode;
}

void Handle::setLastReducedNode(std::optional<std::shared_ptr<ASTNode>> lastReducedNode) {
    _lastReducedNode = lastReducedNode;
}

void Handle::clearLastReducedNode() {
    _lastReducedNode = {};
}

std::optional<std::shared_ptr<ASTNode>> Handle::getPeekNode() {
    return _peekNode;
}

void Handle::setPeekNode(std::optional<std::shared_ptr<ASTNode>> peekNode) {
    _peekNode = peekNode;
}

void Handle::clearPeekNode() {
    _peekNode = {};
}

std::optional<std::shared_ptr<ASTNode>> Handle::getPrevNodeFor(int index) {
    if (index == 0) {
        return this->getLastReducedNode();
    }

    return this->at(index - 1);
}

std::optional<std::shared_ptr<ASTNode>> Handle::getNextNodeFor(int index) {
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

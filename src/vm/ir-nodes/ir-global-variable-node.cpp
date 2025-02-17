//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-global-variable-node.h"

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* irType, std::vector<IRGlobalVariableNode*> childGlobalVariables) {
    _irValue = irValue;
    _type = irType;
    _parentGlobalVariable = {};
    _childGlobalVariables = childGlobalVariables;
    _childGlobalVariableMap = {};
}

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* irType, std::unordered_map<std::string, IRGlobalVariableNode*> childGlobalVariableMap) {
    _irValue = irValue;
    _type = irType;
    _parentGlobalVariable = {};
    _childGlobalVariables = {};
    _childGlobalVariableMap = childGlobalVariableMap;
}

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type, IRGlobalVariableNode* parentGlobalVariable) {
    _irValue = irValue;
    _type = type;
    _parentGlobalVariable = parentGlobalVariable;
    _childGlobalVariables = {};
    _childGlobalVariableMap = {};
}

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type) {
    _irValue = irValue;
    _type = type;
    _parentGlobalVariable = {};
    _childGlobalVariables = {};
    _childGlobalVariableMap = {};
}

llvm::GlobalVariable* IRGlobalVariableNode::getValue() {
    return _irValue;
}

std::optional<IRGlobalVariableNode*> IRGlobalVariableNode::getParent() {
    return _parentGlobalVariable;
}

std::vector<IRGlobalVariableNode*>* IRGlobalVariableNode::getChildGlobalVariables() {
    return &_childGlobalVariables;
}

bool IRGlobalVariableNode::hasChildGlobalVariableMap() {
    return !_childGlobalVariableMap.empty();
}

IRGlobalVariableNode* IRGlobalVariableNode::getChildGlobalVariableForKey(std::string key) {
    auto result = _childGlobalVariableMap.find(key);
    if (result == _childGlobalVariableMap.end()) {
        throw std::invalid_argument("no child global variable found for key: " + key);
    } else {
        return result->second;
    }
}

IRPointerType* IRGlobalVariableNode::getIRType() {
    return _type;
}

IRNodeType IRGlobalVariableNode::getNodeType() {
    return IR_GLOBAL_VARIABLE_NODE;
}

std::string IRGlobalVariableNode::toString() {
    return "IR_GLOBAL_VARIABLE_NODE";
}

void IRGlobalVariableNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}
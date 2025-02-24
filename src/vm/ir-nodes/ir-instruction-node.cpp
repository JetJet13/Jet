//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"
#include "../../shared/utils/logger/logger.h"
#include <utility>

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::optional<IRInstructionNode*> parentAllocation) {
    _irValue = irValue;
    _irType = irType;
    _parentAllocation = parentAllocation;
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, IRInstructionNode* parentAllocation, std::vector<IRInstructionNode*> childAllocations) {
    _irValue = irValue;
    _irType = irType;
    _parentAllocation = parentAllocation;
    _childAllocations = std::move(childAllocations);
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations) {
    _irValue = irValue;
    _irType = irType;
    _parentAllocation = {};
    _childAllocations = std::move(childAllocations);
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap) {
    _irValue = irValue;
    _irType = irType;
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::move(childAllocationMap);
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType) {
    _irValue = irValue;
    _irType = irType;
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

bool IRInstructionNode::isGlobal() {
    return _isGlobal;
}

void IRInstructionNode::markAsGlobal() {
    _isGlobal = true;
    if (_parentAllocation) {
        _parentAllocation.value()->markAsGlobal();
    }
    for (auto childAllocation : _childAllocations) {
        childAllocation->markAsGlobal();
    }
    for (auto keyValue : _childAllocationMap) {
        keyValue.second->markAsGlobal();
    }
}

llvm::Value* IRInstructionNode::getValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRInstructionNode::getParentAllocation() {
    return _parentAllocation;
}

std::vector<IRInstructionNode*>* IRInstructionNode::getChildAllocations() {
    return &_childAllocations;
}

llvm::Type* IRInstructionNode::getAllocatedType() {
    if (llvm::isa<llvm::AllocaInst>(_irValue)) {
        return llvm::cast<llvm::AllocaInst>(_irValue)->getAllocatedType();
    } else if (llvm::isa<llvm::GlobalVariable>(_irValue)) {
        return llvm::cast<llvm::GlobalVariable>(_irValue)->getValueType();
    }
    return _irValue->getType();
}

bool IRInstructionNode::hasChildAllocationMap() {
    return !_childAllocationMap.empty();
}

IRInstructionNode* IRInstructionNode::getChildAllocationForKey(std::string key) {
    auto result = _childAllocationMap.find(key);
    if (result == _childAllocationMap.end()) {
        throw std::invalid_argument("no child allocation found for key: " + key);
    } else {
        return result->second;
    }
}

void IRInstructionNode::setParentAllocation(IRInstructionNode* parentAllocation) {
    _parentAllocation = parentAllocation;
}

llvm::MaybeAlign IRInstructionNode::getAlignment() {
    if (llvm::isa<llvm::AllocaInst>(_irValue)) {
        return llvm::cast<llvm::AllocaInst>(_irValue)->getAlign();
    }
    return llvm::cast<llvm::GlobalVariable>(_irValue)->getAlign();
}

uint64_t IRInstructionNode::getSizeInBytes() {
    return _irType->getSourceType()->getSizeInBytes();
}

IRPointerType* IRInstructionNode::getIRType() {
    return _irType;
}

IRNodeType IRInstructionNode::getNodeType() {
    return IR_ALLOCATION_NODE;
}

std::string IRInstructionNode::toString() {
    return "IR_ALLOCATION_NODE";
}

void IRInstructionNode::printChildAllocations() {
    Logger::log("--------CHILD_ALLOCATIONS--------");
    for (auto childAllocation : _childAllocationMap) {
        Logger::log(childAllocation.first);
    }
    Logger::log("---------------------------------");
}


void IRInstructionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}
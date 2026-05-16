//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"
#include "ir-block-nodes/ir-block-node.h"
#include "../../shared/utils/logger/logger.h"
#include <utility>

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::optional<IRInstructionNode*> parentAllocation) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::vector<llvm::Value*>();
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = parentAllocation;
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::optional<IRInstructionNode*> parentAllocation) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::move(ancestorValues);
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = parentAllocation;
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, IRInstructionNode* parentAllocation, std::vector<IRInstructionNode*> childAllocations) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::vector<llvm::Value*>();
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = parentAllocation;
    _childAllocations = std::move(childAllocations);
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::vector<llvm::Value*>();
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = {};
    _childAllocations = std::move(childAllocations);
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::vector<IRInstructionNode*> childAllocations) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::move(ancestorValues);
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = {};
    _childAllocations = std::move(childAllocations);
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::move(ancestorValues);
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::vector<llvm::Value*> descendentValues) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::move(ancestorValues);
    _descendentValues = std::move(descendentValues);
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::unordered_map<std::string, IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::move(ancestorValues);
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::move(childAllocationMap);
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::vector<llvm::Value*>();
    _descendentValues = std::vector<llvm::Value*>();
    _parentAllocation = {};
    _childAllocations = std::vector<IRInstructionNode*>();
    _childAllocationMap = std::move(childAllocationMap);
}

IRInstructionNode::IRInstructionNode(llvm::Value* irValue, IRPointerType* irType) {
    _irValue = irValue;
    _irType = irType;
    _ancestorValues = std::vector<llvm::Value*>();
    _descendentValues = std::vector<llvm::Value*>();
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

bool IRInstructionNode::isInserted() {
    if (llvm::isa<llvm::Instruction>(_irValue)) {
        return llvm::cast<llvm::Instruction>(_irValue)->getParent() != nullptr;
    } else if (llvm::isa<llvm::ExtractValueInst>(_irValue)) {
        return llvm::cast<llvm::ExtractValueInst>(_irValue)->getParent() != nullptr;
    }
    return false;
}

bool IRInstructionNode::isValueGlobalVariable() {
    return llvm::isa<llvm::GlobalVariable>(_irValue);
}

llvm::Value* IRInstructionNode::getValue() {
    return _irValue;
}

std::vector<llvm::Value*>* IRInstructionNode::getAncestorValues() {
    return &_ancestorValues;
}

std::vector<llvm::Value*>* IRInstructionNode::getDescendentValues() {
    return &_descendentValues;
}

std::optional<IRInstructionNode*> IRInstructionNode::getParentAllocation() {
    return _parentAllocation;
}

std::vector<IRInstructionNode*>* IRInstructionNode::getChildAllocations() {
    return &_childAllocations;
}

void IRInstructionNode::insertAncestorValue(llvm::Value* ancestorValue) {
    _ancestorValues.push_back(ancestorValue);
}

void IRInstructionNode::insertDescendentValue(llvm::Value* descendentValue) {
    _descendentValues.push_back(descendentValue);
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

void IRInstructionNode::setParentAllocation(std::optional<IRInstructionNode*> parentAllocation) {
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
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
// Created by Johny Georges on 2024-07-27.
//

#include "ir-instruction-node-factory.h"

#include <utility>
#include "../address-space-generator/address-space-generator.h"

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::GlobalVariable* globalVariable) {
    return std::make_shared<IRInstructionNode>(globalVariable, IRPointerType::create(globalVariable));
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::GlobalVariable* globalVariable, std::shared_ptr<IRPointerType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
    return std::make_shared<IRInstructionNode>(
            globalVariable,
            irType,
            sourceAllocation);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType) {
    return std::make_shared<IRInstructionNode>(irValue, irType);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues) {
    return std::make_shared<IRInstructionNode>(irValue, irType, ancestorValues);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations) {
    return std::make_shared<IRInstructionNode>(irValue, irType, childAllocations);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations) {
    return std::make_shared<IRInstructionNode>(irValue, irType, ancestorValues, childAllocations);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
    return std::make_shared<IRInstructionNode>(irValue, irType, ancestorValues, sourceAllocation);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap) {
    return std::make_shared<IRInstructionNode>(irValue, irType, ancestorValues, childAllocationMap);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceInstructionNode) {
    return std::make_shared<IRInstructionNode>(irValue, irType, sourceInstructionNode);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRInstructionNode> otherInstructionNode) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    otherInstructionNode->getAllocatedType(),
                    AddressSpaceGenerator::generate(otherInstructionNode->getIRType()->getSourceType()),
                    nullptr,
                    otherInstructionNode->getIRType()->getSourceType()->getAlignment()),
            otherInstructionNode->getIRType()
    );
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRInstructionNode> otherInstructionNode, std::shared_ptr<IRInstructionNode> sourceInstructionNode) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    otherInstructionNode->getAllocatedType(),
                    AddressSpaceGenerator::generate(otherInstructionNode->getIRType()->getSourceType()),
                    nullptr,
                    otherInstructionNode->getIRType()->getSourceType()->getAlignment()),
            otherInstructionNode->getIRType(),
            sourceInstructionNode
    );
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment()), irType);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment()), irType, std::move(childAllocationMap));
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, llvm::Value* numElements) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    numElements,
                    irType->getSourceType()->getAlignment()), irType);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRInstructionNode> sourceAllocation) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment()),
            irType,
            sourceAllocation);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment()),
            irType,
            childAllocations);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRType> irType, std::shared_ptr<IRInstructionNode> sourceAllocation) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment()),
            IRPointerType::create(irType),
            sourceAllocation);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRType> irType) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    irType->getAlignment()),
            IRPointerType::create(irType));
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, std::string name) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment(),
                    name), irType);
}

std::shared_ptr<IRInstructionNode> IRInstructionNodeFactory::create(std::shared_ptr<IRPointerType> irType, std::string name, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
    return std::make_shared<IRInstructionNode>(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    irType->getSourceType()->getAlignment(),
                    name),
            irType,
            sourceAllocation);
}
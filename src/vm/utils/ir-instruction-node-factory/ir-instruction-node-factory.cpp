//
// Created by Johny Georges on 2024-07-27.
//

#include "ir-instruction-node-factory.h"

#include <utility>
#include "../address-space-generator/address-space-generator.h"
#include "../data-alignment-generator/data-alignment-generator.h"

IRInstructionNode* IRInstructionNodeFactory::create(llvm::GlobalVariable* globalVariable) {
    return new IRInstructionNode(globalVariable, IRPointerType::create(globalVariable));
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::GlobalVariable* globalVariable, IRPointerType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    return new IRInstructionNode(
            globalVariable,
            irType,
            sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType) {
    return new IRInstructionNode(irValue, irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues) {
    return new IRInstructionNode(irValue, irType, ancestorValues);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations) {
    return new IRInstructionNode(irValue, irType, childAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::vector<IRInstructionNode*> childAllocations) {
    return new IRInstructionNode(irValue, irType, ancestorValues, childAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::optional<IRInstructionNode*> sourceAllocation) {
    return new IRInstructionNode(irValue, irType, ancestorValues, sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap) {
    return new IRInstructionNode(irValue, irType, ancestorValues, childAllocationMap);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::Value* irValue, IRPointerType* irType, IRInstructionNode* sourceInstructionNode) {
    return new IRInstructionNode(irValue, irType, sourceInstructionNode);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRInstructionNode* otherInstructionNode) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    otherInstructionNode->getAllocatedType(),
                    AddressSpaceGenerator::generate(otherInstructionNode->getIRType()->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(otherInstructionNode->getIRType()->getSourceType())),
            otherInstructionNode->getIRType()
    );
}

IRInstructionNode* IRInstructionNodeFactory::create(IRInstructionNode* otherInstructionNode, IRInstructionNode* sourceInstructionNode) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    otherInstructionNode->getAllocatedType(),
                    AddressSpaceGenerator::generate(otherInstructionNode->getIRType()->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(otherInstructionNode->getIRType()->getSourceType())),
            otherInstructionNode->getIRType(),
            sourceInstructionNode
    );
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::unordered_map<std::string, IRInstructionNode*> childAllocationMap) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())), irType, std::move(childAllocationMap));
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, llvm::Value* numElements) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    numElements,
                    DataAlignmentGenerator::generate(irType->getSourceType())), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())),
            irType,
            sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::vector<IRInstructionNode*> childAllocations) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())),
            irType,
            childAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())),
            IRPointerType::create(irType),
            sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType)),
            IRPointerType::create(irType));
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType()),
                    name), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name, std::optional<IRInstructionNode*> sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType()),
                    name),
            irType,
            sourceAllocation);
}
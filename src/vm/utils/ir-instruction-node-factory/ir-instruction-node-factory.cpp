//
// Created by Johny Georges on 2024-07-27.
//

#include "ir-instruction-node-factory.h"
#include "../address-space-generator/address-space-generator.h"
#include "../data-alignment-generator/data-alignment-generator.h"

IRInstructionNode* IRInstructionNodeFactory::create(llvm::GlobalVariable* globalVariable) {
    return new IRInstructionNode(globalVariable);
}

IRInstructionNode* IRInstructionNodeFactory::create(llvm::AllocaInst* allocaInst, IRPointerType* irType) {
    return new IRInstructionNode(allocaInst, irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::vector<IRExpressionNode*>* childExpressions) {
    auto childSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto childExpression : *childExpressions) {
        childSourceAllocations.push_back(childExpression->getSourceAllocation());
    }
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType())),
            irType,
            childSourceAllocations);
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

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getSourceType()->getType(),
                    AddressSpaceGenerator::generate(irType->getSourceType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getSourceType()),
                    name), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name, IRInstructionNode* sourceAllocation) {
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
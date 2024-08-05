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
                    irType->getPointerSourceIRType()->getType(),
                    AddressSpaceGenerator::generate(irType->getPointerSourceIRType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getPointerSourceIRType())), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::vector<IRExpressionNode*>* childExpressions) {
    auto childSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto childExpression : *childExpressions) {
        childSourceAllocations.push_back(childExpression->getSourceAllocation());
    }
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getPointerSourceIRType()->getType(),
                    AddressSpaceGenerator::generate(irType->getPointerSourceIRType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getPointerSourceIRType())),
            irType,
            childSourceAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getPointerSourceIRType()->getType(),
                    AddressSpaceGenerator::generate(irType->getPointerSourceIRType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getPointerSourceIRType())),
            irType,
            sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::createForArray(IRPointerType* arrayType, IRPointerType* arrayElementType, unsigned long size) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    llvm::ArrayType::get(arrayElementType->getType(), size),
                    AddressSpaceGenerator::generate(arrayElementType),
                    nullptr,
                    DataAlignmentGenerator::generate(arrayElementType)), arrayType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType->getType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getType()),
                    name), irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRPointerType* irType, std::string name, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType->getType()),
                    nullptr,
                    DataAlignmentGenerator::generate(irType->getType()),
                    name),
            irType,
            sourceAllocation);
}
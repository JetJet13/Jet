//
// Created by Johny Georges on 2024-07-27.
//

#include "ir-instruction-node-factory.h"
#include "../address-space-generator/address-space-generator.h"
#include "../data-alignment-generator/data-alignment-generator.h"

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType)),
                    irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, std::vector<IRExpressionNode*>* childExpressions) {
    auto childSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto childExpression : *childExpressions) {
        childSourceAllocations.push_back(childExpression->getSourceAllocation());
    }
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType)),
            irType, childSourceAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, std::vector<llvm::Constant*>* childConstants) {
    auto childSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto childConstant : *childConstants) {
        childSourceAllocations.push_back(IRInstructionNodeFactory::create(new IRType(childConstant->getType())));
    }
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType)),
            irType, childSourceAllocations);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType)),
            irType, sourceAllocation);
}

IRInstructionNode* IRInstructionNodeFactory::createForArray(IRType* arrayType, IRType* arrayElementType, unsigned long size) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    llvm::ArrayType::get(arrayElementType->getType(), size),
                    AddressSpaceGenerator::generate(arrayElementType),
                    nullptr,
                    DataAlignmentGenerator::generate(arrayElementType)),
            arrayType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, std::string name) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType),
                    name),
            irType);
}

IRInstructionNode* IRInstructionNodeFactory::create(IRType* irType, std::string name, IRInstructionNode* sourceAllocation) {
    return new IRInstructionNode(
            new llvm::AllocaInst(
                    irType->getType(),
                    AddressSpaceGenerator::generate(irType),
                    nullptr,
                    DataAlignmentGenerator::generate(irType),
                    name),
            irType, sourceAllocation);
}
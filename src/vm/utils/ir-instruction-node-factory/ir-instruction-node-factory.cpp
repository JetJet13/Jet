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
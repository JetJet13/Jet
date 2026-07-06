//
// Created by Johny Georges on 2024-09-09.
//

#include "ir-load-instruction-node.h"
#include <utility>

IRLoadInstructionNode::IRLoadInstructionNode(llvm::LoadInst* irValue, std::shared_ptr<IRInstructionNode> loadedInstruction) {
    _irValue = irValue;
    _loadedInstruction = loadedInstruction;
}

llvm::LoadInst* IRLoadInstructionNode::getValue() {
    return _irValue;
}

llvm::Type* IRLoadInstructionNode::getType() {
    return _irValue->getType();
}

std::shared_ptr<IRInstructionNode> IRLoadInstructionNode::getLoadedInstruction() {
    return _loadedInstruction;
}

std::shared_ptr<IRType> IRLoadInstructionNode::getIRType() {
    return _loadedInstruction->getIRType()->getSourceType();
}

IRNodeType IRLoadInstructionNode::getNodeType() {
    return IR_LOAD_INSTRUCTION_NODE;
}

std::string IRLoadInstructionNode::toString() {
    return "IR_LOAD_INSTRUCTION_NODE";
}

void IRLoadInstructionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}
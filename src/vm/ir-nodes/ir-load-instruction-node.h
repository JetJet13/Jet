//
// Created by Johny Georges on 2024-09-09.
//

#ifndef JETLANG_IR_LOAD_INSTRUCTION_NODE_H
#define JETLANG_IR_LOAD_INSTRUCTION_NODE_H

#include "ir-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-pointer-type.h"
#include "ir-instruction-node.h"

class IRLoadInstructionNode : public IRNode {
private:
    llvm::LoadInst* _irValue;
    std::shared_ptr<IRInstructionNode> _loadedInstruction;
public:
    IRLoadInstructionNode(llvm::LoadInst* irValue, std::shared_ptr<IRInstructionNode> loadedInstruction);
    llvm::LoadInst* getValue();
    llvm::Type* getType();
    std::shared_ptr<IRInstructionNode> getLoadedInstruction();
    std::shared_ptr<IRType> getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LOAD_INSTRUCTION_NODE_H

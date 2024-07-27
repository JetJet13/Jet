//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_H
#define JETLANG_IR_INSTRUCTION_NODE_H

#include "ir-node.h"
#include "../ir-type/ir-type.h"

class IRInstructionNode : public IRNode {
private:
    llvm::AllocaInst* _irValue;
    IRType* _type;
public:
    IRInstructionNode(llvm::AllocaInst* irValue, IRType* type);
    llvm::AllocaInst* getValue();
    IRType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H

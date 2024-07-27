//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_H
#define JETLANG_IR_INSTRUCTION_NODE_H

#include "ir-node.h"
#include "../ir-type/ir-type.h"

class IRInstructionNode : public IRNode {
private:
    llvm::Instruction* _irValue;
    IRType* _type;
    IRNode* _irNode;
public:
    IRInstructionNode(llvm::Instruction* irValue, IRType* type, IRNode* irNode);
    llvm::Instruction* getValue();
    IRType* getIRType();
    IRNode* getIRNode();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H

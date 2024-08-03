//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_GLOBAL_VARIABLE_NODE_H
#define JETLANG_IR_GLOBAL_VARIABLE_NODE_H

#include "ir-node.h"
#include "ir-instruction-node.h"
#include "../ir-type/ir-pointer-type.h"

class IRGlobalVariableNode : public IRNode {
private:
    llvm::GlobalVariable* _irValue;
    IRPointerType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type, IRInstructionNode* sourceAllocation);
    llvm::GlobalVariable* getValue();
    IRPointerType* getIRType();
    IRInstructionNode* getSourceAllocation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_VARIABLE_NODE_H

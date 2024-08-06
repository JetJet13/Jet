//
// Created by Johny Georges on 2024-08-05.
//

#ifndef JETLANG_IR_ARRAY_NODE_H
#define JETLANG_IR_ARRAY_NODE_H

#include "ir-node.h"
#include "ir-instruction-node.h"
#include "../ir-type/ir-pointer-type.h"

class IRArrayNode : public IRNode {
private:
    unsigned long _size;
    IRPointerType* _type;
    llvm::AllocaInst* _allocation;
public:
    IRArrayNode(IRPointerType* type, unsigned long size, llvm::AllocaInst* allocation);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value* arrayAllocation);
    IRPointerType* getIRType();
    unsigned long getSize();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_NODE_H

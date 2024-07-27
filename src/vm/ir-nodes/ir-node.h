//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_NODE_H
#define JETLANG_IR_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <string>
#include "types/ir-node-type.h"

class IRNode {
public:
    bool is(IRNodeType irNodeType);
    bool isOneOf(std::vector<IRNodeType> irNodeTypes);
    virtual IRNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) = 0;
};

#endif //JETLANG_IR_NODE_H

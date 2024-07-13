//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_STATEMENT_NODE_H
#define JETLANG_IR_STATEMENT_NODE_H

#include "../ir-node.h"

class IRStatementNode : public IRNode {
public:
    virtual llvm::Type* getIRType();
    virtual llvm::Type* getIRTypeAtIndex(unsigned long index);
    virtual llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) = 0;
    virtual llvm::Value* getIRValue() = 0;
};

#endif //JETLANG_IR_STATEMENT_NODE_H

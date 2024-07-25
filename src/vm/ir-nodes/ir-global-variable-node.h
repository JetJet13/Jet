//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_GLOBAL_VARIABLE_NODE_H
#define JETLANG_IR_GLOBAL_VARIABLE_NODE_H

#include "ir-node.h"
#include "../ir-type/ir-type.h"

class IRGlobalVariableNode : public IRNode {
private:
    llvm::GlobalVariable* _irValue;
    IRType* _type;
public:
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRType* type);
    llvm::GlobalVariable* getValue();
    IRType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_VARIABLE_NODE_H

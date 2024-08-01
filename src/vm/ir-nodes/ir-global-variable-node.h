//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_GLOBAL_VARIABLE_NODE_H
#define JETLANG_IR_GLOBAL_VARIABLE_NODE_H

#include "ir-node.h"
#include "ir-instruction-node.h"
#include "../ir-type/ir-struct-type.h"
#include "../ir-type/ir-enum-type.h"

class IRGlobalVariableNode : public IRNode {
private:
    llvm::GlobalVariable* _irValue;
    IREnumType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRGlobalVariableNode(llvm::GlobalVariable* irValue, IREnumType* type, IRInstructionNode* sourceAllocation);
    llvm::GlobalVariable* getValue();
    IREnumType* getIRType();
    IRInstructionNode* getSourceAllocation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_GLOBAL_VARIABLE_NODE_H

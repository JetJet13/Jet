//
// Created by Johny Georges on 2024-07-27.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
#define JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

class IRInstructionNodeFactory {
public:
    static IRInstructionNode* create(llvm::GlobalVariable* globalVariable);
    static IRInstructionNode* create(llvm::AllocaInst* allocaInst);
    static IRInstructionNode* create(IRPointerType* irType);
    static IRInstructionNode* create(IRPointerType* irType, std::vector<IRExpressionNode*>* childExpressions);
    static IRInstructionNode* create(IRPointerType* irType, IRInstructionNode* sourceAllocation);
    static IRInstructionNode* createForArray(IRPointerType* arrayType, IRPointerType* arrayElementType, unsigned long size);
    static IRInstructionNode* create(IRPointerType* irType, std::string name);
    static IRInstructionNode* create(IRPointerType* irType, std::string name, IRInstructionNode* sourceAllocation);
};

#endif //JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

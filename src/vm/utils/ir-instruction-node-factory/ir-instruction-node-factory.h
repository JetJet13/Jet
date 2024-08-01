//
// Created by Johny Georges on 2024-07-27.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
#define JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

class IRInstructionNodeFactory {
public:
    static IRInstructionNode* create(IRType* irType);
    static IRInstructionNode* create(IRType* irType, std::vector<IRExpressionNode*>* childExpressions);
    static IRInstructionNode* create(IRType* irType, std::vector<llvm::Constant*>* childConstants);
    static IRInstructionNode* create(IRType* irType, IRInstructionNode* sourceAllocation);
    static IRInstructionNode* createForArray(IRType* arrayType, IRType* arrayElementType, unsigned long size);
    static IRInstructionNode* create(IRType* irType, std::string name);
    static IRInstructionNode* create(IRType* irType, std::string name, IRInstructionNode* sourceAllocation);
};

#endif //JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

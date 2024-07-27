//
// Created by Johny Georges on 2024-07-27.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
#define JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

#include "../../ir-nodes/ir-instruction-node.h"

class IRInstructionNodeFactory {
public:
    static IRInstructionNode* create(IRType* irType);
    static IRInstructionNode* createForArray(IRType* arrayType, IRType* arrayElementType, unsigned long size);
    static IRInstructionNode* create(IRType* irType, std::string name);
};

#endif //JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

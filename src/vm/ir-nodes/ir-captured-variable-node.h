//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_IR_CAPTURED_VARIABLE_NODE_H
#define JETLANG_IR_CAPTURED_VARIABLE_NODE_H

#include "ir-instruction-node.h"

class IRCapturedVariableNode {
private:
    IRInstructionNode* _mallocVariable;
    IRInstructionNode* _arc;
public:
    IRCapturedVariableNode(IRInstructionNode* mallocVariable, IRInstructionNode* arc);
    IRInstructionNode* getVariable();
    IRInstructionNode* getArc();
};

#endif //JETLANG_IR_CAPTURED_VARIABLE_NODE_H

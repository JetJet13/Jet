//
// Created by Johny Georges on 2026-04-18.
//

#ifndef JETLANG_IR_NODE_TO_FREE_H
#define JETLANG_IR_NODE_TO_FREE_H

#include "ir-node.h"

class IRBlockNode;

class IRNodeToFree {
private:
    IRNode* _irNode;
    IRBlockNode* _irBlock;
public:
    IRNodeToFree(IRNode* irNode, IRBlockNode* irBlock);
    IRNode* getIRNode();
    bool comesBefore(IRBlockNode* irBlockNode);
};

#endif //JETLANG_IR_NODE_TO_FREE_H

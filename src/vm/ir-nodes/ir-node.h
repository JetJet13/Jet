//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_NODE_H
#define JETLANG_IR_NODE_H

#include <string>
#include "types/ir-node-type.h"

class IRNode {
public:
    virtual IRNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
};

#endif //JETLANG_IR_NODE_H

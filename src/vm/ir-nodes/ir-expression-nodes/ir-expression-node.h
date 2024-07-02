//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_EXPRESSION_NODE_H
#define JETLANG_IR_EXPRESSION_NODE_H

#include "../ir-node.h"

class IRExpressionNode : public IRNode {
public:
    virtual void evaluate();
};

#endif //JETLANG_IR_EXPRESSION_NODE_H

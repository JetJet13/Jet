//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_LITERAL_NODE_H
#define JETLANG_IR_LITERAL_NODE_H

#include "../ir-node.h"
#include "../../ir-type/ir-type.h"

class IRLiteralNode : public IRNode {
public:
    virtual llvm::Type* getType();
    virtual IRType* getIRType() = 0;
    virtual llvm::Constant* getConstantIRValue() = 0;
};

#endif //JETLANG_IR_LITERAL_NODE_H

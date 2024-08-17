//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_EXPRESSION_NODE_H
#define JETLANG_IR_EXPRESSION_NODE_H

#include "../ir-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/type-signature/type-signature.h"

class IRExpressionNode : public IRNode {
public:
    virtual llvm::Type* getType();
    virtual llvm::Type* getTypeAtIndex(unsigned long index);
    virtual llvm::Value* getValue() = 0;
    virtual IRType* getIRType() = 0;
    virtual TypeSignature* getTypeSignature() = 0;
};

#endif //JETLANG_IR_EXPRESSION_NODE_H

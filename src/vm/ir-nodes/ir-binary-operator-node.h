//
// Created by Johny Georges on 2026-02-14.
//

#ifndef JETLANG_IR_BINARY_OPERATOR_NODE_H
#define JETLANG_IR_BINARY_OPERATOR_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "ir-expression-nodes/ir-expression-node.h"

class IRBinaryOperatorNode {
private:
    llvm::BinaryOperator* _irOp;
    int _priority;
    bool _isHandled = false;
public:
    IRBinaryOperatorNode(llvm::BinaryOperator* irOp);
    llvm::BinaryOperator* getOp();
    bool isHandled();
    void markAsHandled();
    [[nodiscard]] int getPriority() const;
    bool isHigherPriorityThan(IRBinaryOperatorNode* other) const;
};

#endif //JETLANG_IR_BINARY_OPERATOR_NODE_H

//
// Created by Johny Georges on 2026-02-13.
//

#ifndef JETLANG_IR_BINARY_ARITHMETIC_NODE_H
#define JETLANG_IR_BINARY_ARITHMETIC_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "ir-expression-nodes/ir-expression-node.h"

class IRBinaryArithmeticNode {
private:
    llvm::BinaryOperator* _irOp;
    int _priority;
    bool _isHandled = false;
    int _leftOperandIndex;
    int _rightOperandIndex;
public:
    IRBinaryArithmeticNode(llvm::BinaryOperator* irOp, int leftOperandIndex, int rightOperandIndex);
    llvm::BinaryOperator* getOp();
    int getLeftOperandIndex();
    int getRightOperandIndex();
    bool isHandled();
    void markAsHandled();
    bool isIntAddition();
    bool isIntSubtraction();
    bool isIntMultiplication();
    bool isFloatAddition();
    bool isFloatSubtraction();
    bool isFloatMultiplication();
    int getPriority() const;
    bool isHigherPriorityThan(IRBinaryArithmeticNode* other) const;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_NODE_H

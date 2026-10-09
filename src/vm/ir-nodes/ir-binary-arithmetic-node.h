// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    bool isHigherPriorityThan(std::shared_ptr<IRBinaryArithmeticNode> other) const;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_NODE_H

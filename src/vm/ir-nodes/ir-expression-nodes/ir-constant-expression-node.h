//
// Created by Johny Georges on 2024-07-09.
//

#ifndef JETLANG_IR_CONSTANT_EXPRESSION_NODE_H
#define JETLANG_IR_CONSTANT_EXPRESSION_NODE_H

#include <llvm/IR/Constant.h>
#include "ir-expression-node.h"

class IRConstantExpressionNode : public IRExpressionNode {
public:
     llvm::Constant* getIRValue() override = 0;
};

#endif //JETLANG_IR_CONSTANT_EXPRESSION_NODE_H

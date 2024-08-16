//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_STRATEGY_H
#define JETLANG_IR_INJECTOR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

class IRInjectorMap;

class IRInjectorStrategy {
public:
    virtual llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) = 0;
};

#endif //JETLANG_IR_INJECTOR_STRATEGY_H

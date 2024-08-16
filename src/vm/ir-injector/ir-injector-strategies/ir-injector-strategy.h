//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_STRATEGY_H
#define JETLANG_IR_INJECTOR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

class IRInjectorMap;
class IRExpressionNode;

class IRInjectorStrategy {
protected:
    IRInjectorMap* _irInjectorMap;
public:
    IRInjectorStrategy(IRInjectorMap* irInjectorMap);
    virtual llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) = 0;
};

#endif //JETLANG_IR_INJECTOR_STRATEGY_H

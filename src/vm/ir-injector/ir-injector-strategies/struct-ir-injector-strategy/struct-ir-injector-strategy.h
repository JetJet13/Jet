//
// Created by Johny Georges on 2024-08-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H
#define JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"

class IRStructExpressionNode;
class IRIdentifierExpressionNode;

class StructIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"


class TupleIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) override;
    llvm::Value* inject(IRTupleExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap);
};

#endif //JETLANG_TUPLE_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_STRING_IR_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"


class StringIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) override;
    llvm::Value* inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap);
    llvm::Value* inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap);
};

#endif //JETLANG_STRING_IR_INJECTOR_STRATEGY_H

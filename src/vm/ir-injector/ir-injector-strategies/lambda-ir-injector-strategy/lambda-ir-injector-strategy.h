//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"

class LambdaIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) override;
    llvm::Value* inject(IRLambdaExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* inject(IRLambdaWithFatArrowExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>* builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope);
};


#endif //JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

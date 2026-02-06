//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-block-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "strategies/lambda-ir-object-access-expression-injector-strategy/lambda-ir-object-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-tuple-access-expression-injector-strategy/lambda-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/lambda-ir-array-access-expression-injector-strategy/lambda-ir-array-access-expression-injector-strategy.h"

class LambdaIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    LambdaIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = LambdaIRObjectAccessExpressionInjectorStrategy();
    LambdaIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = LambdaIRTupleAccessExpressionInjectorStrategy();
    LambdaIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = LambdaIRArrayAccessExpressionInjectorStrategy();
    llvm::Value* injectDetails(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    llvm::Value* inject(IRLambdaWithBlockExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    llvm::Value* inject(IRLambdaWithFatArrowExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};


#endif //JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2026-06-01.
//

#ifndef JETLANG_LAMBDA_IR_LAMBDA_WITH_BLOCK_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_LAMBDA_WITH_BLOCK_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-block-expression-node.h"

class LambdaIRLambdaWithBlockExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRLambdaWithBlockExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_LAMBDA_IR_LAMBDA_WITH_BLOCK_EXPRESSION_INJECTOR_STRATEGY_H

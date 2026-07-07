//
// Created by Johny Georges on 2026-06-01.
//

#ifndef JETLANG_LAMBDA_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"

class LambdaIRLambdaWithFatArrowExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRLambdaWithFatArrowExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_LAMBDA_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_INJECTOR_STRATEGY_H

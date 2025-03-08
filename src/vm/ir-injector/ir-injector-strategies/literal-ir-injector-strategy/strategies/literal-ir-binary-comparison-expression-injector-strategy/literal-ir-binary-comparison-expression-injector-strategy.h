//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_LITERAL_IR_BINARY_COMPARISON_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_BINARY_COMPARISON_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"

class LiteralIRBinaryComparisonExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRBinaryComparisonExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_LITERAL_IR_BINARY_COMPARISON_EXPRESSION_INJECTOR_STRATEGY_H

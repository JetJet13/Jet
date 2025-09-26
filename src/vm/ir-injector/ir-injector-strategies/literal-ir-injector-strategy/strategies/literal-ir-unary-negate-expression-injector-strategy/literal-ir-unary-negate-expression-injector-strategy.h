//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_LITERAL_IR_UNARY_NEGATE_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_UNARY_NEGATE_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"

class LiteralIRUnaryNegateExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRUnaryNegateExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};


#endif //JETLANG_LITERAL_IR_UNARY_NEGATE_EXPRESSION_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2025-03-07.
//

#ifndef JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"

class LiteralIRBinaryArithmeticExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRBinaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};


#endif //JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H

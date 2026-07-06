//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_LITERAL_IR_UNARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_UNARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"

class LiteralIRUnaryArithmeticExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRUnaryArithmeticExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};


#endif //JETLANG_LITERAL_IR_UNARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H

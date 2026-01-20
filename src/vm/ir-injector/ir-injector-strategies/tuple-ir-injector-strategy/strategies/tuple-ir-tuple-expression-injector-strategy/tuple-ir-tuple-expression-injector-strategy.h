//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_TUPLE_IR_TUPLE_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_IR_TUPLE_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"

class TupleIRTupleExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRTupleExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};


#endif //JETLANG_TUPLE_IR_TUPLE_EXPRESSION_INJECTOR_STRATEGY_H

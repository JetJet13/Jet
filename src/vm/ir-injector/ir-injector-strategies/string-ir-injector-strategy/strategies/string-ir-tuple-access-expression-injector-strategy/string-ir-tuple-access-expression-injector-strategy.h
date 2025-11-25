//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_STRING_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"

class StringIRTupleAccessExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_STRING_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

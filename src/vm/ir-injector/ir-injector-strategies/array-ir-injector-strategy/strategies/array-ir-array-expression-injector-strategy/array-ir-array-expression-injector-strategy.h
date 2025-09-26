//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_ARRAY_IR_ARRAY_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_IR_ARRAY_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"

class ArrayIRArrayExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRArrayExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};


#endif //JETLANG_ARRAY_IR_ARRAY_EXPRESSION_INJECTOR_STRATEGY_H

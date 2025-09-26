//
// Created by Johny Georges on 2025-04-25.
//

#ifndef JETLANG_ARRAY_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

class ArrayIRIdentifierExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_ARRAY_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

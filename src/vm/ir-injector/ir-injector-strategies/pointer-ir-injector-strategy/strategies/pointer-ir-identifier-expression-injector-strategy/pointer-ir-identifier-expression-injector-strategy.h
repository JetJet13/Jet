//
// Created by Johny Georges on 2025-03-15.
//

#ifndef JETLANG_POINTER_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

class PointerIRIdentifierExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_POINTER_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

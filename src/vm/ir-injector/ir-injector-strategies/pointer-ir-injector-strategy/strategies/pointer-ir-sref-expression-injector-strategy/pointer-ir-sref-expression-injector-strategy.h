//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_POINTER_IR_SREF_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_SREF_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-sref-expression-node.h"

class PointerIRSrefExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRSrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_POINTER_IR_SREF_EXPRESSION_INJECTOR_STRATEGY_H

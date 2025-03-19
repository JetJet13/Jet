//
// Created by Johny Georges on 2025-03-19.
//

#ifndef JETLANG_STRUCT_IR_DREF_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRUCT_IR_DREF_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

class StructIRDrefExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_STRUCT_IR_DREF_EXPRESSION_INJECTOR_STRATEGY_H

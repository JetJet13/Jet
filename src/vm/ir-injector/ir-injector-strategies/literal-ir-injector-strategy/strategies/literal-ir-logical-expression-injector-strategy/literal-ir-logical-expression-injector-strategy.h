//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-logical-expression-node.h"


class LiteralIRLogicalExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRLogicalExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};


#endif //JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H

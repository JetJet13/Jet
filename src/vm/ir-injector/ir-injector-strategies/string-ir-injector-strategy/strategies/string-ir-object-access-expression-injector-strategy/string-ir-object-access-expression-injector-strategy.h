//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_STRING_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"

class StringIRObjectAccessExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_STRING_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

//
// Created by Johny Georges on 2025-06-09.
//

#ifndef JETLANG_STRING_IR_CONCAT_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_CONCAT_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-concat-expression-node.h"

class StringIRConcatExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRConcatExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};


#endif //JETLANG_STRING_IR_CONCAT_EXPRESSION_INJECTOR_STRATEGY_H

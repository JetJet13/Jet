//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-ref-expression-node.h"

class RefIRRefExpressionInjectorStrategy {
private:
    llvm::Value* injectRawValue(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_REF_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H

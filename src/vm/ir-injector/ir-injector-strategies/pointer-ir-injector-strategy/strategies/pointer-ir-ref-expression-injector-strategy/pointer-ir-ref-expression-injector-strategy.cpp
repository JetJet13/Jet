//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-ref-expression-injector-strategy.h"

llvm::Value* PointerIRRefExpressionInjectorStrategy::inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
}
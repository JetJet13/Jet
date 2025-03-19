//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-identifier-expression-injector-strategy.h"

llvm::Value* PointerIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}
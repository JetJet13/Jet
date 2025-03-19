//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-ref-expression-injector-strategy.h"

llvm::Value* PointerIRRefExpressionInjectorStrategy::inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->getExpression()->isOneOf({ IR_IDENTIFIER_EXPRESSION_NODE, IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        return irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    }
    return this->injectRawValue(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
}

llvm::Value* PointerIRRefExpressionInjectorStrategy::injectRawValue(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto rawValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperationType, irModule, scope);
    if (irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getIRType()->getSourceType()->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->insertGlobalVariable(globalVariable);
        irBlock->getBuilder()->get()->CreateStore(rawValue, globalVariable);
        return globalVariable;
    }

    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getType());
    irBlock->getBuilder()->get()->CreateStore(rawValue, allocation);
    return allocation;
}
//
// Created by Johny Georges on 2025-07-28.
//

#include "literal-ir-literal-expression-injector-strategy.h"

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::inject(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    switch (irOperationType) {
        case IR_REF_ASSIGNMENT_OP:
        case IR_REF_GLOBAL_ASSIGNMENT_OP:
            return this->injectRef(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        case IR_COPY_ASSIGNMENT_OP:
        case IR_COPY_GLOBAL_ASSIGNMENT_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectCopy(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectRef(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), literalAllocation);
    return literalAllocation;
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectOperand(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return irExpression->getValue();
    }
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
//    irBlock->getBuilder()->get()->CreateCall(irModule->getPrintDebugPointerFunction(), { literalAllocation });
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), literalAllocation);
    return literalAllocation;
}
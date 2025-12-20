//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-identifier-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-struct-pointer-type.h"

llvm::Value* TupleIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* TupleIRIdentifierExpressionInjectorStrategy::injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return StructIRInjectorHelper::injectStructCopy(
            irBlock,
            (IRStructRefType*)irExpression->getUnderlyingIRType(),
            irExpression->getValue(),
            irModule,
            irInjector
    );
}

llvm::Value* TupleIRIdentifierExpressionInjectorStrategy::injectRef(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* TupleIRIdentifierExpressionInjectorStrategy::injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue()) {
        if (irExpression->getIRType()->containsTypeThatRequiresFreeing()) {
            auto irType = irExpression->getIRType()->getSourceType();
            auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irType->getType());
            auto typeValue = irInjector->inject(irBlock, irType);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
            irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyStructRefFunction(),
                {
                    destinationPointerAllocation,
                    irExpression->getValue(),
                    loadedTypeValue
                }
            );
            return InstructionIRInjectorHelper::injectLoad(irType->getType(), destinationPointerAllocation, irBlock);
        }
        return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), irExpression->getValue(), irBlock, irExpression->getUnderlyingIRType());
    }
    return irExpression->getValue();
}
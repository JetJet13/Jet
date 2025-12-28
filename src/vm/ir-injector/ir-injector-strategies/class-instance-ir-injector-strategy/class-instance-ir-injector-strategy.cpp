//
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* ClassInstanceIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("ClassInstanceIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* ClassInstanceIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isCopy()) {
        auto irType = (IRStructRefType*)irExpression->getIRType()->getSourceType();
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
    return irExpression->getValue();
}

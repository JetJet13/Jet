//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-identifier-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
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

llvm::Value* StructIRIdentifierExpressionInjectorStrategy::injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return StructIRInjectorHelper::injectStructCopy(
            irBlock,
            (IRStructType*)irExpression->getIRType()->getSourceType(),
            irExpression->getValue(),
            irModule,
            irInjector
    );
}

llvm::Value* StructIRIdentifierExpressionInjectorStrategy::injectRef(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* StructIRIdentifierExpressionInjectorStrategy::injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock);
//        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
    }
    return irExpression->getValue();
}
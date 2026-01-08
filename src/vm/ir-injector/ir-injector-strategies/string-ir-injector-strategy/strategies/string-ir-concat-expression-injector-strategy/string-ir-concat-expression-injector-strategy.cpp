//
// Created by Johny Georges on 2025-06-09.
//

#include "string-ir-concat-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRConcatExpressionInjectorStrategy::inject(IRConcatExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irLeftValue = irInjector->inject(irBlock, irExpression->getLeftNode(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto irRightValue = irInjector->inject(irBlock, irExpression->getRightNode(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    irExpression->getValue()->setArgOperand(0, irLeftValue);
    irExpression->getValue()->setArgOperand(1, irRightValue);
    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}
//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getUnderlyingIRType();
    auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, arrayAccessAllocation);
    auto alloc = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType, irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyArrayFunction(),
            {
                alloc,
                pointer,
                loadedTypeValue
            }
    );
    return InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getType(), alloc, irBlock);
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectRef(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    return ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, loadedPointerToIndexedElement);
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, loadedPointerToIndexedElement);
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), pointer, irBlock);
    }
    return pointer;
}
//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* StructIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* StructIRTupleAccessExpressionInjectorStrategy::injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedSourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    return StructIRInjectorHelper::injectStructRefCopy(
            irBlock,
            (IRStructRefType *) irExpression->getSource()->getIRType(),
            loadedSourceAllocation,
            irModule,
            irInjector
    );
}

llvm::Value* StructIRTupleAccessExpressionInjectorStrategy::injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedSourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, loadedSourceAllocation);
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
    }
    return pointer;
}
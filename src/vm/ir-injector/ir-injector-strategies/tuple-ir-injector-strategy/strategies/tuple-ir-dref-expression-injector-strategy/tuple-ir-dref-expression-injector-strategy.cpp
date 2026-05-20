//
// Created by Johny Georges on 2026-05-19.
//

#include "tuple-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto irType = (IRStructRefType *)irExpression->getIRType();
    StructIRInjectorHelper::injectStructRefCopy(
            irBlock,
            irType,
            pointerToValue,
            allocation,
            irModule,
            irInjector
    );
    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irType->getType(), allocation, irBlock, irType);
}
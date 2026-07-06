//
// Created by Johny Georges on 2025-06-21.
//

#include "dref-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-ref-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* DrefIRInjectorHelper::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getExpression()->getIRType()->getSourceType());
    auto refValue = irInjector->inject(irBlock, irExpression->getExpression(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    if (irOperation->isOperandPointer()) {
        return refValue;
    }
    return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), refValue, irBlock, irRefType->getRefValueIRType());
}
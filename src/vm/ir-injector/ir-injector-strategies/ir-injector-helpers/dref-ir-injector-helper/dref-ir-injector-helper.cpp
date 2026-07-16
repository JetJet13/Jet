//
// Created by Johny Georges on 2025-06-21.
//

#include "dref-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-shared-ptr-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* DrefIRInjectorHelper::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irExpression->getExpression()->getIRType()->getSourceType());
    auto sharedValue = irInjector->inject(irBlock, irExpression->getExpression(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    if (irOperation->isOperandPointer()) {
        return sharedValue;
    }
    return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), sharedValue, irBlock, irSharedPtrType->getSharedValueIRType());
}
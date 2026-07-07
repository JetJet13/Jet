//
// Created by Johny Georges on 2025-03-19.
//

#include "array-ir-dref-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRDrefExpressionInjectorStrategy::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    auto irArrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getIRType());
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType, irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { allocation, pointerValue, loadedTypeValue });
    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getType(), allocation, irBlock, irArrayPointerType);
}
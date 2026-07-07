//
// Created by Johny Georges on 2025-03-19.
//

#include "struct-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRDrefExpressionInjectorStrategy::inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock, "YYLL");
    auto irType = std::dynamic_pointer_cast<IRStructRefType>(irExpression->getIRType());
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
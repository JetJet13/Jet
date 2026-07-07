//
// Created by Johny Georges on 2025-03-15.
//

#include "pointer-ir-ref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRRefExpressionInjectorStrategy::inject(std::shared_ptr<IRRefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(value, irExpression->getIRType()->getType()->getPointerTo());
        InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
        return allocation;
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(irExpression->getExpression()->getValue(), irExpression->getIRType()->getType()->getPointerTo());
        InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
        return allocation;
    }
    auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(value, irExpression->getIRType()->getType()->getPointerTo());
    InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
    return allocation;
}

llvm::Value* PointerIRRefExpressionInjectorStrategy::injectRawValue(std::shared_ptr<IRRefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto rawValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
    if (irOperation->isRefGlobalAssignment()) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getUnderlyingIRType()->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->get()->insertGlobalVariable(globalVariable);
        InstructionIRInjectorHelper::injectStore(rawValue, globalVariable, irBlock, irExpression->getIRRefType()->getRefValueIRType());
        return globalVariable;
    }

    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getExpression()->getType());
    InstructionIRInjectorHelper::injectStore(rawValue, allocation, irBlock, irExpression->getIRRefType()->getRefValueIRType());
    return allocation;
}
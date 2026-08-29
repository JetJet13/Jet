//
// Created by Johny Georges on 2026-08-29.
//

#include "class-method-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ClassMethodAccessIRInjectorHelper::inject(std::shared_ptr<IRClassInstanceMethodAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }
    auto invocableIrType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getIRType()->getSourceType());
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getSourceType()->getType());

    auto loadedMethod = InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock);
    InstructionIRInjectorHelper::injectStore(loadedMethod, allocation, irBlock);
    auto classInstancePointer = irInjector->inject(irBlock, irExpression->getClassInstance(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto classInstanceArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRType()->getSourceType()->getType(), allocation, invocableIrType->getFunctionScopeArgumentIndex());
    InstructionIRInjectorHelper::injectStore(classInstancePointer, classInstanceArgumentPointer, irBlock);
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), allocation, irBlock);
}

llvm::Value* ClassMethodAccessIRInjectorHelper::inject(std::shared_ptr<IRClassStaticMethodAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock);
}
//
// Created by Johny Georges on 2025-07-28.
//

#include "literal-ir-literal-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-generator/ir-util-functions/print-ir-function/print-ir-function.h"

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::inject(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isSharedValueAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectRef(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return irExpression->getValue();
    }
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
    InstructionIRInjectorHelper::injectStore(irExpression->getValue(), literalAllocation, irBlock, irExpression->getIRType());
    return literalAllocation;
}
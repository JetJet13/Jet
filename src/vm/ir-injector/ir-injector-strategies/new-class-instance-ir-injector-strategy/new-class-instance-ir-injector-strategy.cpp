//
// Created by Johny Georges on 2025-01-01.
//

#include "new-class-instance-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->inject((IRNewClassInstanceExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("NewClassInstanceIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRNewClassInstanceExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    auto classInstanceAllocation = InstructionIRInjectorHelper::inject(irExpression->getClassInstanceAllocation(), irBlock);
    auto preConstructorFunction = irModule->getModule()->getFunction(irExpression->getIRType()->getPreConstructorName());
    irBlock->getBuilder()->get()->CreateCall(preConstructorFunction, { classInstanceAllocation });

    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope));
    }
    arguments.push_back(classInstanceAllocation);
    irBlock->getBuilder()->get()->CreateCall(
            irExpression->getConstructorIRType()->getType(),
            irExpression->getConstructorFunction(),
            arguments
    );
    return InstructionIRInjectorHelper::injectLoad(
            irExpression->getClassInstanceAllocation()->getIRType()->getUnderlyingType()->getType(),
            classInstanceAllocation,
            irBlock
    );
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getUnderlyingIRType()->getType(), irExpression->getValue(), irBlock);
    }
    return irExpression->getValue();
}
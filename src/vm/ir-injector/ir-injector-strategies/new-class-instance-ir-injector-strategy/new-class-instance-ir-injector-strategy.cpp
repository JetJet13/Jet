//
// Created by Johny Georges on 2025-01-01.
//

#include "new-class-instance-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->inject((IRNewClassInstanceExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("NewClassInstanceIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRNewClassInstanceExpressionNode* irNewClassInstanceExpressionNode, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto classInstanceAllocation = InstructionIRInjectorHelper::inject(irNewClassInstanceExpressionNode->getClassInstanceAllocation(), irBlock);
    auto preConstructorFunction = irModule->getModule()->getFunction(irNewClassInstanceExpressionNode->getIRType()->getPreConstructorName());
    irBlock->getBuilder()->get()->CreateCall(preConstructorFunction, { classInstanceAllocation });

    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irNewClassInstanceExpressionNode->getIRArguments()) {
        arguments.push_back(irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope));
    }
    arguments.push_back(classInstanceAllocation);
    irBlock->getBuilder()->get()->CreateCall(
            irNewClassInstanceExpressionNode->getConstructorIRType()->getType(),
            irNewClassInstanceExpressionNode->getConstructorFunction(),
            arguments
    );
    return InstructionIRInjectorHelper::injectLoad(
            irNewClassInstanceExpressionNode->getClassInstanceAllocation()->getIRType()->getUnderlyingType()->getType(),
            classInstanceAllocation,
            irBlock
    );
//    return irBlock->getBuilder()->get()->CreateLoad(
//        irNewClassInstanceExpressionNode->getClassInstanceAllocation()->getIRType()->getSourceType()->getType(),
//        classInstanceAllocation
//    );
}
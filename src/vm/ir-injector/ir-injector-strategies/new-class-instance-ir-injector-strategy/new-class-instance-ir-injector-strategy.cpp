//
// Created by Johny Georges on 2025-01-01.
//

#include "new-class-instance-ir-injector-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->inject((IRNewClassInstanceExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    } else if (irExpression->is(IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return ClassPropertyAccessIRInjectorHelper::inject((IRClassStaticPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    }
    throw std::logic_error("NewClassInstanceIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRNewClassInstanceExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irStructRefType = irExpression->getIRType()->getIRClassPropertiesType();
    auto classInstanceAllocation = InstructionIRInjectorHelper::inject(irExpression->getClassInstanceAllocation(), irBlock);
    auto classInstancePropertiesAllocation = InstructionIRInjectorHelper::inject(irExpression->getClassInstanceAllocation()->getParentAllocation().value(), irBlock);
    auto pointerToClassInstancePropertiesPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), classInstanceAllocation, irStructRefType->getStructIndex());
    InstructionIRInjectorHelper::injectStore(classInstancePropertiesAllocation, pointerToClassInstancePropertiesPointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), classInstanceAllocation, irStructRefType->getCounterIndex());
    auto arc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    InstructionIRInjectorHelper::injectStore(arc, pointerToCounterPointer, irBlock);

    auto preConstructorFunction = irModule->getModule()->get()->getFunction(irExpression->getIRType()->getIRClassType()->getPreConstructorName());
    irBlock->getBuilder()->get()->CreateCall(preConstructorFunction, { classInstanceAllocation });

    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope));
    }
    arguments.push_back(classInstanceAllocation);
    auto constructorFunction = irModule->getModule()->get()->getFunction(irExpression->getConstructorId());
    irBlock->getBuilder()->get()->CreateCall(
            constructorFunction,
            arguments
    );

    if (irOperation->isOperandPointer()) {
        return classInstanceAllocation;
    }


    return InstructionIRInjectorHelper::injectLoad(
            irExpression->getClassInstanceAllocation()->getIRType()->getUnderlyingType()->getType(),
            classInstanceAllocation,
            irBlock
    );
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isCopy()) {
        auto irType = (IRNewClassInstanceType*)irExpression->getIRType()->getSourceType();
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irType->getType());
        auto typeValue = irInjector->inject(irBlock, irType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStructRefFunction(),
            {
                destinationPointerAllocation,
                irExpression->getValue(),
                loadedTypeValue
            }
        );
        return InstructionIRInjectorHelper::injectLoad(irType->getType(), destinationPointerAllocation, irBlock);
    }
    return irExpression->getValue();
}

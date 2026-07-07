//
// Created by Johny Georges on 2026-02-20.
//

#include "class-property-ref-value-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-struct-ref-type.h"
#include "../../../ir-type/ir-ref-type.h"

void ClassPropertyRefValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRClassPropertyRefValueAssignmentStatementNode> irClassPropertyRefValueAssignmentStatementNode, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto classScopeParameter = scope->getClassScope().value();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto classInstanceIrType = std::dynamic_pointer_cast<IRStructRefType>(classScopeParameter->getIRType()->getUnderlyingType());
    auto pointerToClassInstancePropertiesAlloc = irBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), loadedPointer, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classInstanceIrType->getStructType(), pointerToClassInstancePropertiesAlloc, irBlock);

    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(
            classInstanceIrType->getStructIRType()->getType(),
            classInstancePropertiesAlloc,
            irClassPropertyRefValueAssignmentStatementNode->getPropertyIndex()
    );
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(classInstanceIrType->getStructIRType()->getIRTypeByIndex(irClassPropertyRefValueAssignmentStatementNode->getPropertyIndex()));
    auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), pointer, irRefType->getRefValueIndex());
    auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    if (irRefType->getUnderlyingType()->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { loadedPointerToRefValue, loadedTypeValue }
        );
    }
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertyRefValueAssignmentStatementNode->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    InstructionIRInjectorHelper::injectStore(irExpressionValue, loadedPointerToRefValue, irBlock, irClassPropertyRefValueAssignmentStatementNode->getExpression()->getIRType());
}
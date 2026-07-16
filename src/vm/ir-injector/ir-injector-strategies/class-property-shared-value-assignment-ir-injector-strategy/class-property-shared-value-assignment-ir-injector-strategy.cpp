//
// Created by Johny Georges on 2026-02-20.
//

#include "class-property-shared-value-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-struct-ref-type.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

void ClassPropertySharedValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRClassPropertySharedValueAssignmentStatementNode> irClassPropertySharedValueAssignmentStatementNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto classScopeParameter = scope->getClassScope().value();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto classInstanceIrType = std::dynamic_pointer_cast<IRStructRefType>(classScopeParameter->getIRType()->getUnderlyingType());
    auto pointerToClassInstancePropertiesAlloc = irBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), loadedPointer, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classInstanceIrType->getStructType(), pointerToClassInstancePropertiesAlloc, irBlock);

    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(
            classInstanceIrType->getStructIRType()->getType(),
            classInstancePropertiesAlloc,
            irClassPropertySharedValueAssignmentStatementNode->getPropertyIndex()
    );
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(classInstanceIrType->getStructIRType()->getIRTypeByIndex(irClassPropertySharedValueAssignmentStatementNode->getPropertyIndex()));
    auto pointerToSharedValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), pointer, irSharedPtrType->getSharedValueIndex());
    auto loadedPointerToSharedValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToSharedValue, irBlock);
    if (irSharedPtrType->getUnderlyingType()->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irSharedPtrType->getUnderlyingType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { loadedPointerToSharedValue, loadedTypeValue }
        );
    }
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertySharedValueAssignmentStatementNode->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    InstructionIRInjectorHelper::injectStore(irExpressionValue, loadedPointerToSharedValue, irBlock, irClassPropertySharedValueAssignmentStatementNode->getExpression()->getIRType());
}
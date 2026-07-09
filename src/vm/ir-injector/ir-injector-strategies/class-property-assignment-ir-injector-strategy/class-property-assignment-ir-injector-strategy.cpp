//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-struct-ref-type.h"

void ClassPropertyAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAssignmentStatementNode> irClassPropertyAssignmentStatementNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto classScopeParameter = scope->getClassScope().value();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto classInstanceIrType = std::dynamic_pointer_cast<IRStructRefType>(classScopeParameter->getIRType()->getUnderlyingType());
    auto irType = classInstanceIrType->getStructIRType()->getIRTypeByIndex(irClassPropertyAssignmentStatementNode->getPropertyIndex());
    auto pointerToClassInstancePropertiesAlloc = irBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), loadedPointer, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classInstanceIrType->getStructType(), pointerToClassInstancePropertiesAlloc, irBlock);

    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(
        classInstanceIrType->getStructIRType()->getType(),
        classInstancePropertiesAlloc,
        irClassPropertyAssignmentStatementNode->getPropertyIndex()
    );
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertyAssignmentStatementNode->getExpression(), std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    if (irType->getSourceType()->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType->getSourceType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeClassPropertyFunction(),
                { pointer, loadedTypeValue }
        );
    }
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irClassPropertyAssignmentStatementNode->getExpression()->getIRType());
}
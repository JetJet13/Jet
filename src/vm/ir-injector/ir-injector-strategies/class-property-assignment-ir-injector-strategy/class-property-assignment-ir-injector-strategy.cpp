//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-struct-pointer-type.h"

void ClassPropertyAssignmentIRInjectorStrategy::inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto classScopeParameter = scope->getClassScope().value();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto classInstanceIrType = (IRStructRefType*)classScopeParameter->getIRType()->getUnderlyingType();
    auto pointerToClassInstancePropertiesAlloc = irBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), loadedPointer, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classInstanceIrType->getStructType(), pointerToClassInstancePropertiesAlloc, irBlock);

    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(
        classInstanceIrType->getStructIRType()->getType(),
        classInstancePropertiesAlloc,
        irClassPropertyAssignmentStatementNode->getPropertyIndex()
    );
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertyAssignmentStatementNode->getExpression(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irClassPropertyAssignmentStatementNode->getExpression()->getIRType());
}
//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ClassPropertyAssignmentIRInjectorStrategy::inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertyAssignmentStatementNode->getExpression(), new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    auto classScopeParameter = scope->getClassScope().value();
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(
        classScopeParameter->getIRType()->getUnderlyingType()->getType(),
        loadedPointer,
        irClassPropertyAssignmentStatementNode->getPropertyIndex()
    );
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irClassPropertyAssignmentStatementNode->getExpression()->getIRType());
}
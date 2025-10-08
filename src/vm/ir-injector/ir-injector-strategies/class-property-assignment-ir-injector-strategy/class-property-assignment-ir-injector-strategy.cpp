//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ClassPropertyAssignmentIRInjectorStrategy::inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto irExpressionValue = irInjector->inject(irBlock, irClassPropertyAssignmentStatementNode->getExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto classScopeParameter = scope->getClassScope().value();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto propertyIndex = irBlock->getBuilder()->get()->getInt64(irClassPropertyAssignmentStatementNode->getPropertyIndex());
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(classScopeParameter->getIRType()->getType(), classScopeParameter->getValue(), irBlock);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(
        classScopeParameter->getIRType()->getUnderlyingType()->getType(),
        loadedPointer,
        { zeroIndex, propertyIndex }
    );
    irBlock->getBuilder()->get()->Insert(pointer);
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irClassPropertyAssignmentStatementNode->getExpression()->getIRType());
}
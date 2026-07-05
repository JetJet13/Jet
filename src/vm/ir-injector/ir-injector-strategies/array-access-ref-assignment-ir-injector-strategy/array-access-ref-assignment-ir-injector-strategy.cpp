//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-ref-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"

void ArrayAccessRefAssignmentIRInjectorStrategy::inject(IRArrayAccessRefAssignmentStatementNode* irArrayAccessRefAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToIndexedElement = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irArrayAccessRefAssignmentStatement->getIRArrayAccessExpression(), irModule, irInjector, scope);
    auto newValue = irInjector->inject(
            irBlock,
            irArrayAccessRefAssignmentStatement->getIRExpression(),
            new IROperation(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irArrayAccessRefAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irArrayAccessRefAssignmentStatement->getIRArrayAccessExpression()->getIRType()->getSourceType());
    auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetRefValueFunction(),
            { pointerToIndexedElement, newValueMalloc,  loadedTypeValue }
    );
}
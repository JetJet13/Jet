//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-ref-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"

void TupleAccessRefAssignmentIRInjectorStrategy::inject(IRTupleAccessRefAssignmentStatementNode* irTupleAccessRefAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto objectAccess = irTupleAccessRefAssignmentStatement->getIRTupleAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irTupleAccessRefAssignmentStatement->getIRTupleAccessExpression(), source);
    auto newValue = irInjector->inject(
            irBlock,
            irTupleAccessRefAssignmentStatement->getIRExpression(),
            new IROperation(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irTupleAccessRefAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irRefType = (IRRefType*)irTupleAccessRefAssignmentStatement->getIRTupleAccessExpression()->getIRType()->getSourceType();
    auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetRefValueFunction(),
            { pointerToTarget, newValueMalloc,  loadedTypeValue }
    );
}
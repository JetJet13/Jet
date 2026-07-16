//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-shared-value-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

void ObjectAccessSharedValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRObjectAccessSharedValueAssignmentStatementNode> irObjectAccessSharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto objectAccess = irObjectAccessSharedValueAssignmentStatement->getIRObjectAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irObjectAccessSharedValueAssignmentStatement->getIRObjectAccessExpression(), source);
    auto newValue = irInjector->inject(
            irBlock,
            irObjectAccessSharedValueAssignmentStatement->getIRExpression(),
            std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irObjectAccessSharedValueAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irObjectAccessSharedValueAssignmentStatement->getIRObjectAccessExpression()->getIRType()->getSourceType());
    auto typeValue = irInjector->inject(irBlock, irSharedPtrType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetSharedValueFunction(),
        { pointerToTarget, newValueMalloc,  loadedTypeValue }
    );
}
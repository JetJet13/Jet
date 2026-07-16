//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-shared-value-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

void ModuleAccessSharedValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRModuleAccessSharedValueAssignmentStatementNode> irModuleAccessSharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToTarget = ModuleAccessIRInjectorHelper::inject(irModuleAccessSharedValueAssignmentStatement->getIRModuleAccessExpression(), irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto newValue = irInjector->inject(
            irBlock,
            irModuleAccessSharedValueAssignmentStatement->getIRExpression(),
            std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irModuleAccessSharedValueAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irModuleAccessSharedValueAssignmentStatement->getIRModuleAccessExpression()->getIRType()->getSourceType());
    auto typeValue = irInjector->inject(irBlock, irSharedPtrType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getSetSharedValueFunction(),
        { pointerToTarget, newValueMalloc,  loadedTypeValue }
    );
}
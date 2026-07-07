//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-ref-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"

void ModuleAccessRefAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRModuleAccessRefAssignmentStatementNode> irModuleAccessRefAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToTarget = ModuleAccessIRInjectorHelper::inject(irModuleAccessRefAssignmentStatement->getIRModuleAccessExpression(), irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto newValue = irInjector->inject(
            irBlock,
            irModuleAccessRefAssignmentStatement->getIRExpression(),
            std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irModuleAccessRefAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irModuleAccessRefAssignmentStatement->getIRModuleAccessExpression()->getIRType()->getSourceType());
    auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getSetRefValueFunction(),
        { pointerToTarget, newValueMalloc,  loadedTypeValue }
    );
}
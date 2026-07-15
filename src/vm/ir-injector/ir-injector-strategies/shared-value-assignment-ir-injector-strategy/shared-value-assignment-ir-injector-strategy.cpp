//
// Created by Johny Georges on 2026-02-20.
//

#include "shared-value-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

void SharedValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRSharedValueAssignmentStatementNode> irSharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irType = irSharedValueAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto globalVariable = scope->findGlobalVariable(irSharedValueAssignmentStatement->getVariableName());
    auto newValue = irInjector->inject(
            irBlock,
            irSharedValueAssignmentStatement->getIRExpression(),
            std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
        irModule->getMallocFunction(),
        {
            irBlock->getBuilder()->get()->getInt64(1),
            irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
        }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    if (globalVariable) {
        auto irRefType = std::dynamic_pointer_cast<IRRefType>(globalVariable.value()->getIRType()->getSourceType());
        auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetRefValueFunction(),
            { globalVariable.value()->getValue(), newValueMalloc, loadedTypeValue }
        );
    } else {
        auto variable = scope->find(irSharedValueAssignmentStatement->getVariableName()).value();
        auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(variable->getIRType()->getSourceType());
        auto typeValue = irInjector->inject(irBlock, irSharedPtrType->getUnderlyingType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        DebugIRInjectorHelper::injectLog(irBlock, "SHARED VALUE ASSIGNMENT - FREEING CURRENT VALUE", irInjector, irModule);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getSetRefValueFunction(),
                { variable->getValue(), newValueMalloc,  loadedTypeValue }
        );
    }
}
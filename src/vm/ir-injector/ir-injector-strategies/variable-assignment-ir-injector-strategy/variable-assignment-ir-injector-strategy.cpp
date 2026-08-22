//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void VariableAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRVariableAssignmentStatementNode> irVariableAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto variable = scope->find(irVariableAssignmentStatement->getVariableName());
    auto newVariableValue = irInjector->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
                    irModule,
                    scope
    );
    if (variable) {
        if (variable.value()->getIRType()->getSourceType()->containsTypeThatRequiresFreeing()) {
            auto typeValue = irInjector->inject(irBlock, variable.value()->getIRType()->getSourceType(), irModule);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variable.value()->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction(),
                    { variable.value()->getValue(), loadedTypeValue }
            );
        }
        InstructionIRInjectorHelper::injectStore(newVariableValue, variable.value()->getValue(), irBlock, variable.value()->getIRType());

    } else {
        auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
        auto globalVariableIrType = globalVariable.value()->getIRType()->getSourceType();
        auto newValueAlloc = irBlock->getBuilder()->get()->CreateAlloca(globalVariableIrType->getType());
        InstructionIRInjectorHelper::injectStore(newVariableValue, newValueAlloc, irBlock, globalVariableIrType);
        auto typeValue = irInjector->inject(irBlock, globalVariableIrType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(globalVariableIrType->getValue()->getAllocatedType(), typeValue, irBlock);
        if (globalVariableIrType->containsTypeThatRequiresFreeing()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction(),
                    { globalVariable.value()->getValue(), loadedTypeValue }
            );
        }
        irBlock->getBuilder()->get()->CreateMemCpy(
                globalVariable.value()->getValue(),
                globalVariableIrType->getAlignment(),
                newValueAlloc,
                globalVariableIrType->getAlignment(),
                globalVariableIrType->getSizeInBytes()
        );

    }
}
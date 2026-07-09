//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void VariableAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRVariableAssignmentStatementNode> irVariableAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    auto newVariableValue = irInjector->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
                    irModule,
                    scope
    );
    if (globalVariable) {
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
    } else {
        auto variable = scope->find(irVariableAssignmentStatement->getVariableName()).value();
        if (variable->getIRType()->getSourceType()->containsTypeThatRequiresFreeing()) {
            auto typeValue = irInjector->inject(irBlock, variable->getIRType()->getSourceType(), irModule);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(variable->getIRType()->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction(),
                    { variable->getValue(), loadedTypeValue }
            );
        }
        InstructionIRInjectorHelper::injectStore(newVariableValue, variable->getValue(), irBlock, variable->getIRType());
    }
}
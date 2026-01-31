//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    auto newVariableValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, scope);
    if (globalVariable) {
        auto globalVariableIrType = globalVariable.value()->getIRType()->getSourceType();
        auto newValueAlloc = irBlock->getBuilder()->get()->CreateAlloca(globalVariableIrType->getType());
        InstructionIRInjectorHelper::injectStore(newVariableValue, newValueAlloc, irBlock, globalVariableIrType);
        auto typeValue = irInjector->inject(irBlock, globalVariableIrType);
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
        InstructionIRInjectorHelper::injectStore(newVariableValue, variable->getValue(), irBlock, variable->getIRType());
    }
}
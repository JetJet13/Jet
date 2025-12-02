//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    auto operation = globalVariable.has_value() ? (new IROperation(IR_COPY_ASSIGNMENT_OP))->markAsGlobal() : new IROperation(IR_COPY_ASSIGNMENT_OP);
    auto newVariableValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    operation, irModule, scope);
    if (globalVariable) {
        auto oldGlobalVariableValue = InstructionIRInjectorHelper::injectLoad(globalVariable.value()->getAllocatedType(), globalVariable.value()->getValue(), irBlock);
        auto globalVariableIrType = globalVariable.value()->getIRType()->getSourceType();
        irBlock->getBuilder()->get()->CreateMemCpy(
                globalVariable.value()->getValue(),
                globalVariableIrType->getAlignment(),
                newVariableValue,
                globalVariableIrType->getAlignment(),
                globalVariableIrType->getSizeInBytes()
        );
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction()->getFunctionType(),
                irModule->getFreeValueFunction(),
                { oldGlobalVariableValue }
        );

    } else {
        auto variable = scope->find(irVariableAssignmentStatement->getVariableName()).value();
        InstructionIRInjectorHelper::injectStore(newVariableValue, variable->getValue(), irBlock, variable->getIRType());
    }
}
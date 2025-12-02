//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    InstructionIRInjectorHelper::inject(irVariableDeclaration->getIRValue(), irBlock, irVariableDeclaration->getVariableName());
    auto operation = this->determineOperationType(irVariableDeclaration);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableDeclaration->getIRExpression(),
                    operation, irModule, scope);

      InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getValue(), irBlock, irVariableDeclaration->getAllocatedIRType());
    if (irVariableDeclaration->getGlobalVariable()) {
        InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getGlobalVariable().value()->getValue(), irBlock, irVariableDeclaration->getGlobalVariable().value()->getIRType());
    }
    if (irVariableDeclaration->needsToBeFreed()) {
        irBlock->addVariableToFree(irVariableDeclaration);
    }
}

IROperation* VariableIRInjectorStrategy::determineOperationType(IRVariableDeclarationNode* irVariableDeclaration) {
    auto operation = irVariableDeclaration->getIRExpression()->is(IR_REF_EXPRESSION_NODE)
            ? new IROperation(IR_REF_ASSIGNMENT_OP)
            : new IROperation(IR_COPY_ASSIGNMENT_OP);
    if (irVariableDeclaration->getGlobalVariable()) {
        operation->markAsGlobal();
    }
    return operation;
}
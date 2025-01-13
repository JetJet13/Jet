//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    IR_OPERAND_OP, irModule, scope);
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    if (globalVariable) {
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            globalVariable.value()->getValue()
        );
    } else {
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            scope->find(irVariableAssignmentStatement->getVariableName()).value()->getValue()
        );
    }
}
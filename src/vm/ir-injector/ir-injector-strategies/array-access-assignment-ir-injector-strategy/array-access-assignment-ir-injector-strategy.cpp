//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-ir-injector-strategy.h"

void ArrayAccessAssignmentIRInjectorStrategy::inject(IRArrayAccessAssignmentStatementNode* irArrayAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irAssignmentValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRArrayAccessExpression(),
                    IR_COPY_REASSIGNMENT_OP, irModule, scope
            );
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRExpression(),
                    IR_OPERAND_VALUE_OP, irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irAssignmentValue);
}
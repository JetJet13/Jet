//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-ir-injector-strategy.h"

void ObjectAccessAssignmentIRInjectorStrategy::inject(IRObjectAccessAssignmentStatementNode* irObjectAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irAssignmentValue = irInjector
            ->inject(
                    irBlock,
                    irObjectAccessAssignmentStatement->getIRObjectAccessExpression(),
                    IR_COPY_REASSIGNMENT_OP, irModule, scope
            );
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irObjectAccessAssignmentStatement->getIRExpression(),
                    IR_OPERAND_VALUE_OP, irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irAssignmentValue);
}
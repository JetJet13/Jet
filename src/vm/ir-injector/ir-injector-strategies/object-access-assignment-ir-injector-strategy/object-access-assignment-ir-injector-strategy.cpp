//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-ir-injector-strategy.h"

void ObjectAccessAssignmentIRInjectorStrategy::inject(IRObjectAccessAssignmentStatementNode* irObjectAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto objectAccess = irObjectAccessAssignmentStatement->getIRObjectAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointerToTarget = llvm::GetElementPtrInst::CreateInBounds(objectAccess->getSource()->getIRType()->getSourceType()->getType(), source, { irBlock->getBuilder()->get()->getInt64(0), objectAccess->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointerToTarget);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irObjectAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointerToTarget);
}
//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-ir-injector-strategy.h"

void TupleAccessAssignmentIRInjectorStrategy::inject(IRTupleAccessAssignmentStatementNode* irTupleAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto objectAccess = irTupleAccessAssignmentStatement->getIRTupleAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = llvm::GetElementPtrInst::CreateInBounds(objectAccess->getSource()->getIRType()->getSourceType()->getType(), source, { irBlock->getBuilder()->get()->getInt64(0), objectAccess->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointerToTarget);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irTupleAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointerToTarget);
}
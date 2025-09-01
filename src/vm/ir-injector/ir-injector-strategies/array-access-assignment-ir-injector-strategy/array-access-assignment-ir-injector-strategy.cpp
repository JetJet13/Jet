//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"

void ArrayAccessAssignmentIRInjectorStrategy::inject(IRArrayAccessAssignmentStatementNode* irArrayAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto arrayPointerType = (IRArrayPointerType*)irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getSourceExpression()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto indexValue = irInjector->inject(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(
            arrayPointerType->getType(),
            sourceValue,
            { zeroIndex, allocIndex }
    );
    auto arrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), arrayAllocPointer);
    auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRExpression(),
                    IR_OPERAND_VALUE_OP, irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
}
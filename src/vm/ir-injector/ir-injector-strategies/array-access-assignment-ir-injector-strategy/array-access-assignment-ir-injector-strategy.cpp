//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ArrayAccessAssignmentIRInjectorStrategy::inject(IRArrayAccessAssignmentStatementNode* irArrayAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto arrayPointerType = (IRArrayPointerType*)irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getSourceExpression()->getUnderlyingIRType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    auto indexValue = irInjector->inject(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(
            arrayPointerType->getType(),
            sourceValue,
            { zeroIndex, allocIndex }
    );
//    auto arrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), arrayAllocPointer);
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), arrayAllocPointer, irBlock, arrayPointerType);
    auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRExpression(),
                    IR_OPERAND_VALUE_OP, irModule, scope
            );
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irArrayAccessAssignmentStatement->getIRExpression()->getIRType());
//    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
}
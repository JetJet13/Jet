//
// Created by Johny Georges on 2026-06-27.
//

#include "class-static-property-ref-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"

void ClassStaticPropertyRefAssignmentIRInjectorStrategy::inject(IRClassStaticPropertyRefAssignmentStatementNode* irClassStaticPropertyRefAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToTarget = ClassPropertyAccessIRInjectorHelper::inject(irClassStaticPropertyRefAssignmentStatement->getIRClassStaticPropertyAccessExpressionNode(),irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_POINTER_OP));
    auto newValue = irInjector->inject(
            irBlock,
            irClassStaticPropertyRefAssignmentStatement->getIRExpression(),
            new IROperation(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irClassStaticPropertyRefAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irRefType = (IRRefType*)irClassStaticPropertyRefAssignmentStatement->getIRClassStaticPropertyAccessExpressionNode()->getIRType()->getSourceType();
    auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetRefValueFunction(),
            { pointerToTarget, newValueMalloc,  loadedTypeValue }
    );
}
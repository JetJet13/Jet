//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void TupleAccessAssignmentIRInjectorStrategy::inject(IRTupleAccessAssignmentStatementNode* irTupleAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto objectAccess = irTupleAccessAssignmentStatement->getIRTupleAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irTupleAccessAssignmentStatement->getIRTupleAccessExpression(), source);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irTupleAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );
    auto irType = irTupleAccessAssignmentStatement->getIRTupleAccessExpression()->getIRType()->getSourceType();
    if (irType->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType->clone());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { pointerToTarget, loadedTypeValue }
        );
    }
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointerToTarget);
}
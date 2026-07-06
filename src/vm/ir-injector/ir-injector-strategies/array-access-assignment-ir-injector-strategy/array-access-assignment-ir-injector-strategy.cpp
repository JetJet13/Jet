//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

void ArrayAccessAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRArrayAccessAssignmentStatementNode> irArrayAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToIndexedElement = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression(), irModule, irInjector, scope);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );

    auto irType = irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getIRType()->getSourceType();
    if (irType->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { pointerToIndexedElement, loadedTypeValue }
        );
    }

    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToIndexedElement, irBlock, irArrayAccessAssignmentStatement->getIRExpression()->getIRType());
}
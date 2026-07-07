//
// Created by Johny Georges on 2026-03-16.
//

#include "class-static-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ClassStaticPropertyAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRClassStaticPropertyAssignmentStatementNode> irClassStaticPropertyAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToTarget = ClassPropertyAccessIRInjectorHelper::inject(irClassStaticPropertyAssignmentStatement->getIRClassStaticPropertyAccessExpressionNode(),irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irClassStaticPropertyAssignmentStatement->getIRExpression(),
                    std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope
            );
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToTarget, irBlock);
}
//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ModuleAccessAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRModuleAccessAssignmentStatementNode> irModuleAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToTarget = ModuleAccessIRInjectorHelper::inject(irModuleAccessAssignmentStatement->getIRModuleAccessExpression(), irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto irType = irModuleAccessAssignmentStatement->getIRModuleAccessExpression()->getIRType();
    auto irExpressionValue = irInjector
            ->inject(
                irBlock,
                irModuleAccessAssignmentStatement->getIRExpression(),
                std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope
            );
    if (irType->getSourceType()->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType->getSourceType(), irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getSourceType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { pointerToTarget, loadedTypeValue }
        );
    }
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToTarget, irBlock);
}
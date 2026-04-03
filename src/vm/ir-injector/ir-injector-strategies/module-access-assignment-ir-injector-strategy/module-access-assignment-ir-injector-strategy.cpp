//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ModuleAccessAssignmentIRInjectorStrategy::inject(IRModuleAccessAssignmentStatementNode* irModuleAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToTarget = ModuleAccessIRInjectorHelper::inject(irModuleAccessAssignmentStatement->getIRModuleAccessExpression(), irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_POINTER_OP));
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irModuleAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToTarget, irBlock);
}
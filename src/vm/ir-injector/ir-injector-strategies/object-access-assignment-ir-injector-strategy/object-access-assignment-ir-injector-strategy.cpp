//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

void ObjectAccessAssignmentIRInjectorStrategy::inject(IRObjectAccessAssignmentStatementNode* irObjectAccessAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto objectAccess = irObjectAccessAssignmentStatement->getIRObjectAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irObjectAccessAssignmentStatement->getIRObjectAccessExpression(), source);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irObjectAccessAssignmentStatement->getIRExpression(),
                    new IROperation(IR_OPERAND_VALUE_OP), irModule, scope
            );
    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointerToTarget);
}
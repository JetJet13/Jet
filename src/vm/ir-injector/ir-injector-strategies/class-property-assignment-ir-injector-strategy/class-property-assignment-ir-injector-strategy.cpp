//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

void ClassPropertyAssignmentIRInjectorStrategy::inject(IRClassPropertyAssignmentStatementNode* irClassPropertyAssignmentStatementNode, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule, IRLookupTable* scope) {
    auto irExpressionValue = irInjectorMap->getInjector(irClassPropertyAssignmentStatementNode->getExpression()->getTypeSignature())->inject(irClassPropertyAssignmentStatementNode->getExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    auto classScopeParameter = scope->getClassScope().value();
    auto zeroIndex = builder->get()->getInt32(0);
    auto propertyIndex = builder->get()->getInt32(irClassPropertyAssignmentStatementNode->getPropertyIndex());
    auto pointerToProperty = builder->get()->CreateInBoundsGEP(classScopeParameter->getAllocatedType(), classScopeParameter->getValue(), { zeroIndex, propertyIndex });
    builder->get()->CreateStore(irExpressionValue, pointerToProperty);
}
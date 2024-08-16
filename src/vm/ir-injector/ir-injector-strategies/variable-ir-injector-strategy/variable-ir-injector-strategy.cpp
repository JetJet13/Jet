//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    builder->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    auto irExpressionValue = irInjectorMap->getInjector(irVariableDeclaration->getIRExpression()->getTypeSignature())->inject(irVariableDeclaration->getIRExpression(), builder, irInjectorMap);
    builder->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
}
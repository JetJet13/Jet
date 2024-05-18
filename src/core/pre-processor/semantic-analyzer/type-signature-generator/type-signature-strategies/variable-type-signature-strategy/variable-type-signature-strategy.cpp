//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"

TypeSignature* VariableTypeSignatureStrategy::create(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        auto result = strategyMap->getTypeSignatureForType(variableDeclaration->getVarInitNode()->getTypeNode().value(), scope);
        return result;
    }
    return strategyMap->getTypeSignatureForExpression(variableDeclaration->getInitializerNode(), scope);
}
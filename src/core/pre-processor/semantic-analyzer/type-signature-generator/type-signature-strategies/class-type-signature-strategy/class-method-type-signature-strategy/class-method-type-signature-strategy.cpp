//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"

ClassMethodTypeSignature* ClassMethodTypeSignatureStrategy::create(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<TypeSignature*> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        returnType = strategyMap->getTypeSignatureForType(classMethodDeclaration->getReturnType().value());
    }
// todo: fix UNKNOWN_TYPE_SIGNATURE for class methods that return a class instance: 'this' or 'MyClass'
    return new ClassMethodTypeSignature(
            strategyMap->getTypeSignatureForAccessModifier(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()),
            strategyMap->getTypeSignatureForParameterList(classMethodDeclaration->getParameters()),
            classMethodDeclaration->getClassMethodDefinition()->isStatic(),
            returnType
    );
}
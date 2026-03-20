//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ClassMethodTypeSignatureStrategy::assign(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<TypeSignature*> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        strategyMap->assignTypeSignatureFor(classMethodDeclaration->getReturnType().value(), context, scope);
        returnType = classMethodDeclaration->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier(), context, scope);
    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getParameters(), context, scope);

    classMethodDeclaration->setTypeSignature(
            new ClassMethodTypeSignature(
                classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()->getTypeSignature(),
                classMethodDeclaration->getParameters()->getTypeSignature(),
                classMethodDeclaration->getClassMethodDefinition()->isStatic(),
                returnType
    ));
}
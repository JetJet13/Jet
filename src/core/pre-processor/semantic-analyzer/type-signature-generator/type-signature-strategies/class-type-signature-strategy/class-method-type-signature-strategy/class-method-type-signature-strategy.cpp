//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ClassMethodTypeSignatureStrategy::assign(std::shared_ptr<ASTClassMethodDeclarationNode> classMethodDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<std::shared_ptr<TypeSignature>> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        strategyMap->assignTypeSignatureFor(classMethodDeclaration->getReturnType().value(), context, scope);
        returnType = classMethodDeclaration->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier(), context, scope);
    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getParameters(), context, scope);

    classMethodDeclaration->setTypeSignature(
            std::make_shared<ClassMethodTypeSignature>(
                classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()->getAccessModifierTypeSignature(),
                classMethodDeclaration->getParameters()->getParameterListTypeSignature(),
                classMethodDeclaration->getClassMethodDefinition()->isStatic(),
                returnType
    ));
}
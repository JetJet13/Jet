//
// Created by Johny Georges on 2024-05-27.
//

#include "class-declaration-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"

void ClassDeclarationTypeCheckerPolicy::apply(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(classDeclarationNode, typeCheckerResult);

}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(classDeclarationNode, typeCheckerResult);
}

void ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    for (auto classProperty : *classDeclarationNode->getBlock()->getProperties()) {
        if (classProperty->getInitializer()) {
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                classProperty->getTypeSignature(),
                classProperty->getInitializer().value()->getTypeSignature(),
                TypeCheckerErrorMessageTable::ClassPropertyInitializerTypeMismatch,
                typeCheckerResult
            );
        }
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classPropertyNames = std::vector<std::string>();
    for (auto classProperty : *classDeclarationNode->getBlock()->getProperties()) {
        classPropertyNames.push_back(classProperty->getId());
    }

    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &classPropertyNames,
        TypeCheckerErrorMessageTable::ClassPropertyNamesNotUnique,
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(classDeclarationNode, typeCheckerResult);

    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        TypeChecker::applyPolicyTo(classMethod->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(classMethod->getBlock(), typeCheckerResult);
        if (classMethod->getTypeSignature()->getReturnType()) {
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                classMethod->getTypeSignature()->getReturnType().value(),
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeUnknown,
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeInvalid,
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeVoid,
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                classMethod->getBlock(),
                classMethod->getTypeSignature()->getReturnType().value(),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                TypeCheckerErrorMessageTable::ClassMethodNotAllPathsReturn,
                typeCheckerResult
            );
        } else {
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                typeCheckerResult
            );
        }
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classMethodNameAndTypeSignatureList = std::vector<std::pair<std::string, TypeSignature*>>();
    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        classMethodNameAndTypeSignatureList.emplace_back(
            std::pair(
                classMethod->getClassMethodDefinition()->getMethodName()->getId(),
                classMethod->getTypeSignature()
            )
        );
    }

    TypeCheckerRuleProvider::getUniqueTypeSignatureWithIdTypeCheckerRule()
    ->enforce(
        &classMethodNameAndTypeSignatureList,
        TypeCheckerErrorMessageTable::ClassMethodNamesAndTypeSignaturesNotUnique,
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(classDeclarationNode, typeCheckerResult);
    for (auto classConstructor : *classDeclarationNode->getBlock()->getConstructors()) {
        TypeChecker::applyPolicyTo(classConstructor->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(classConstructor->getBlock(), typeCheckerResult);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            classConstructor->getBlock(),
            typeCheckerResult
        );
    }

}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classConstructorTypeSignatures = std::vector<TypeSignature*>();
    for (auto classConstructor : *classDeclarationNode->getBlock()->getConstructors()) {
        classConstructorTypeSignatures.push_back(classConstructor->getTypeSignature());
    }

    TypeCheckerRuleProvider::getUniqueTypeSignaturesTypeCheckerRule()
            ->enforce(
                    &classConstructorTypeSignatures,
                    TypeCheckerErrorMessageTable::ClassConstructorsNotUnique,
                    typeCheckerResult
            );
}

//
// Created by Johny Georges on 2024-05-27.
//

#include "class-declaration-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"
#include "../../../../../../shared/utils/logger/logger.h"

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
        if (classProperty->getTypeSignature()->getType()->isInvocable()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::ClassPropertyInvocable(classProperty));
        }

        if (classProperty->getInitializer()) {
            Logger::log("Class property initializer", classProperty->getId());
            classProperty->getTypeSignature()->getType()->print();
            classProperty->getInitializer().value()->getTypeSignature()->print();
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                classProperty->getTypeSignature()->getType(),
                classProperty->getInitializer().value()->getTypeSignature(),
                TypeCheckerErrorMessageTable::ClassPropertyInitializerTypeMismatch(classProperty),
                typeCheckerResult
            );
        }
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classPropertyNames = std::vector<ASTIdentifierNode*>();
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &classPropertyNames,
        TypeCheckerErrorMessageTable::ClassPropertyNamesNotUnique(classDeclarationNode),
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(classDeclarationNode, typeCheckerResult);

    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        TypeChecker::applyPolicyTo(classMethod->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(classMethod->getBlock(), typeCheckerResult);
        if (!classMethod->getTypeSignature()->getReturnType()->isVoid()) {
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                classMethod->getTypeSignature()->getReturnType(),
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeUnknown(
                    classMethod
                ),
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeInvalid(
                    classMethod
                ),
                TypeCheckerErrorMessageTable::ClassMethodReturnTypeVoid(
                    classMethod
                ),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                classMethod->getBlock(),
                classMethod->getTypeSignature()->getReturnType(),
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                TypeCheckerErrorMessageTable::ClassMethodNotAllPathsReturn(
                    classMethod
                ),
                typeCheckerResult
            );
        } else {
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                TypeCheckerErrorMessageTable::ClassMethodHasReturnExpression(
                    classMethod
                ),
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
        TypeCheckerErrorMessageTable::ClassMethodNamesAndTypeSignaturesNotUnique(
            classDeclarationNode
        ),
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
            TypeCheckerErrorMessageTable::ClassConstructorHasReturnExpression(
                classConstructor
            ),
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
                    TypeCheckerErrorMessageTable::ClassConstructorsNotUnique(classDeclarationNode),
                    typeCheckerResult
            );
}

//
// Created by Johny Georges on 2024-05-27.
//

#include "class-declaration-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"
#include "../../../../../../shared/utils/logger/logger.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void ClassDeclarationTypeCheckerPolicy::apply(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(classDeclarationNode, typeCheckerResult);
    if (!classDeclarationNode->getTypeSignature()->satisfiesImplementInterfaces()) {
        typeCheckerResult->addError(TypeCheckerErrorMessageTable::ClassDoesNotImplementInterface(classDeclarationNode)());
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(classDeclarationNode, typeCheckerResult);
}

void ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    for (auto classProperty : *classDeclarationNode->getBlock()->getProperties()) {
        if (classProperty->getTypeSignature()->getType()->isInvocable()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::ClassPropertyInvocable(classProperty)());
        }

        auto selfReferenceErrorMessage = TypeCheckerErrorMessageTable::ClassPropertySelfReference(classProperty);
        TypeCheckerRuleProvider::getClassSelfReferenceTypeCheckerRule()->enforce(classDeclarationNode->getTypeSignature(), classProperty->getTypeSignature(), selfReferenceErrorMessage, typeCheckerResult);

        auto circularReferenceErrorMessage = TypeCheckerErrorMessageTable::ClassPropertyCircularReference(classProperty);
        TypeCheckerRuleProvider::getClassCircularReferenceTypeCheckerRule()->enforce(classDeclarationNode->getTypeSignature(), classProperty->getTypeSignature(), circularReferenceErrorMessage, typeCheckerResult);

        if (classProperty->getInitializer()) {
            auto mismatchMessage = TypeCheckerErrorMessageTable::ClassPropertyInitializerTypeMismatch(classProperty);
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                classProperty->getTypeSignature()->getType(),
                classProperty->getInitializer().value()->getTypeSignature(),
                mismatchMessage,
                typeCheckerResult
            );
        }
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classPropertyNames = std::vector<std::shared_ptr<ASTIdentifierNode>>();
    auto namesNotUniqueErrorMessage = TypeCheckerErrorMessageTable::ClassPropertyNamesNotUnique(classDeclarationNode);
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
    ->enforce(
        &classPropertyNames,
        namesNotUniqueErrorMessage,
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(classDeclarationNode, typeCheckerResult);

    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        TypeChecker::applyPolicyTo(classMethod->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(classMethod->getBlock(), typeCheckerResult);
        if (!classMethod->getTypeSignature()->getReturnType()->isVoid()) {
            auto unknownMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeUnknown(classMethod);
            auto invalidMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeInvalid(classMethod);
            auto voidMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeVoid(classMethod);
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                classMethod->getTypeSignature()->getReturnType(),
                unknownMessage,
                invalidMessage,
                voidMessage,
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                classMethod->getBlock(),
                classMethod->getTypeSignature()->getReturnType(),
                typeCheckerResult
            );
            auto notAllPathsReturnMessage = TypeCheckerErrorMessageTable::ClassMethodNotAllPathsReturn(classMethod);
            TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                notAllPathsReturnMessage,
                typeCheckerResult
            );
        } else {
            auto methodNoReturnMessage = TypeCheckerErrorMessageTable::ClassMethodHasReturnExpression(classMethod);
            TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
                classMethod->getBlock(),
                methodNoReturnMessage,
                typeCheckerResult
            );
        }
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classMethodNameAndTypeSignatureList = std::vector<std::pair<std::string, TypeSignature*>>();
    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        classMethodNameAndTypeSignatureList.emplace_back(
            std::pair(
                classMethod->getClassMethodDefinition()->getMethodName()->getId(),
                classMethod->getTypeSignature()
            )
        );
    }

    auto methodNamesNotUniqueMessage = TypeCheckerErrorMessageTable::ClassMethodNamesAndTypeSignaturesNotUnique(classDeclarationNode);
    TypeCheckerRuleProvider::getUniqueTypeSignatureWithIdTypeCheckerRule()
    ->enforce(
        &classMethodNameAndTypeSignatureList,
        methodNamesNotUniqueMessage,
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(classDeclarationNode, typeCheckerResult);
    for (auto classConstructor : *classDeclarationNode->getBlock()->getConstructors()) {
        TypeChecker::applyPolicyTo(classConstructor->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(classConstructor->getBlock(), typeCheckerResult);
        auto noReturnExpressionMessage = TypeCheckerErrorMessageTable::ClassConstructorHasReturnExpression(classConstructor);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            classConstructor->getBlock(),
            noReturnExpressionMessage,
            typeCheckerResult
        );
    }

}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classConstructorTypeSignatures = std::vector<TypeSignature*>();
    for (auto classConstructor : *classDeclarationNode->getBlock()->getConstructors()) {
        classConstructorTypeSignatures.push_back(classConstructor->getTypeSignature());
    }
    auto classConstructorsNotUnique = TypeCheckerErrorMessageTable::ClassConstructorsNotUnique(classDeclarationNode);
    TypeCheckerRuleProvider::getUniqueTypeSignaturesTypeCheckerRule()
            ->enforce(
                    &classConstructorTypeSignatures,
                    classConstructorsNotUnique,
                    typeCheckerResult
            );
}

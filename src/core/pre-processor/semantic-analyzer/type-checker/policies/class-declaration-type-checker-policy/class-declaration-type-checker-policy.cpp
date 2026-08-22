//
// Created by Johny Georges on 2024-05-27.
//

#include "class-declaration-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../type-checker.h"
#include "../../../../../../shared/utils/logger/logger.h"

void ClassDeclarationTypeCheckerPolicy::apply(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(classDeclarationNode, typeCheckerResult, fileScope);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(classDeclarationNode, typeCheckerResult, fileScope);
    TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()->enforce(classDeclarationNode, typeCheckerResult);
    if (!classDeclarationNode->getClassTypeSignature()->satisfiesImplementInterfaces()) {
        typeCheckerResult->addError(TypeCheckerErrorMessageTable::ClassDoesNotImplementInterface(classDeclarationNode)());
    }
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassProperties(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {

    ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(classDeclarationNode, typeCheckerResult);
    ClassDeclarationTypeCheckerPolicy::verifyAllClassPropertyNamesAreUnique(classDeclarationNode, typeCheckerResult);
}

void ClassDeclarationTypeCheckerPolicy::verifyClassPropertiesWithInitializer(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    for (auto classProperty : *classDeclarationNode->getBlock()->getProperties()) {
        if (classProperty->getPropertyTypeSignature()->getType()->isInvocable()) {
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::ClassPropertyInvocable(classProperty)());
        }

        auto selfReferenceErrorMessage = TypeCheckerErrorMessageTable::ClassPropertySelfReference(classProperty);
        TypeCheckerRuleProvider::getClassSelfReferenceTypeCheckerRule()->enforce(classDeclarationNode->getClassTypeSignature(), classProperty->getPropertyTypeSignature(), selfReferenceErrorMessage, typeCheckerResult);

        auto circularReferenceErrorMessage = TypeCheckerErrorMessageTable::ClassPropertyCircularReference(classProperty);
        TypeCheckerRuleProvider::getClassCircularReferenceTypeCheckerRule()->enforce(classDeclarationNode->getClassTypeSignature(), classProperty->getPropertyTypeSignature(), circularReferenceErrorMessage, typeCheckerResult);

        if (classProperty->getInitializer()) {
            auto mismatchMessage = TypeCheckerErrorMessageTable::ClassPropertyInitializerTypeMismatch(classProperty);
            TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
            ->enforce(
                classProperty->getPropertyTypeSignature()->getType(),
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
        classDeclarationNode->getBlock()->getInstanceProperties(),
        typeCheckerResult
    );
}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassMethods(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassMethodsAreUnique(classDeclarationNode, typeCheckerResult);

    for (auto classMethod : *classDeclarationNode->getBlock()->getMethods()) {
        auto classMethodScope = ClassDeclarationTypeCheckerPolicy::generateClassScope(classDeclarationNode, fileScope);
        TypeChecker::applyPolicyTo(classMethod->getParameters(), typeCheckerResult, classMethodScope);
        TypeChecker::applyPolicyTo(classMethod->getBlock(), typeCheckerResult, classMethodScope);
        if (!classMethod->getMethodTypeSignature()->getReturnType()->isVoid()) {
            auto unknownMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeUnknown(classMethod);
            auto invalidMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeInvalid(classMethod);
            auto voidMessage = TypeCheckerErrorMessageTable::ClassMethodReturnTypeVoid(classMethod);
            TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
            ->enforce(
                classMethod->getMethodTypeSignature()->getReturnType(),
                unknownMessage,
                invalidMessage,
                voidMessage,
                typeCheckerResult
            );
            TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule()
            ->enforce(
                classMethod->getBlock(),
                classMethod->getMethodTypeSignature()->getReturnType(),
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
    auto classMethodNameAndTypeSignatureList = std::vector<std::pair<std::string, std::shared_ptr<TypeSignature>>>();
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

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructors(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(classDeclarationNode, typeCheckerResult);
    for (auto classConstructor : *classDeclarationNode->getBlock()->getConstructors()) {
        auto classConstructorScope = ClassDeclarationTypeCheckerPolicy::generateClassScope(classDeclarationNode, fileScope);
        TypeChecker::applyPolicyTo(classConstructor->getParameters(), typeCheckerResult, classConstructorScope);
        TypeChecker::applyPolicyTo(classConstructor->getBlock(), typeCheckerResult, classConstructorScope);
        auto noReturnExpressionMessage = TypeCheckerErrorMessageTable::ClassConstructorHasReturnExpression(classConstructor);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            classConstructor->getBlock(),
            noReturnExpressionMessage,
            typeCheckerResult
        );
    }

}

void ClassDeclarationTypeCheckerPolicy::verifyAllClassConstructorsAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult) {
    auto classConstructorTypeSignatures = std::vector<std::shared_ptr<TypeSignature>>();
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

std::shared_ptr<TypeSignatureLookupTable> ClassDeclarationTypeCheckerPolicy::generateClassScope(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
    auto classScope = std::make_shared<TypeSignatureLookupTable>();
    classScope->markAsClassScope();
    classScope->inheritGlobalScope(fileScope);
    for (auto property : *classDeclarationNode->getBlock()->getProperties()) {
        auto propertyContext = std::make_shared<VariableContext>();
        if (property->isConstant()) {
            propertyContext->markAsConstant();
        }
        classScope->insert(property->getId(), property->getPropertyTypeSignature()->getType());
        classScope->insertVariableContext(property->getId(), propertyContext);
    }

    for (auto property : *classDeclarationNode->getBlock()->getStaticProperties()) {
        auto propertyContext = std::make_shared<VariableContext>();
        if (property->isConstant()) {
            propertyContext->markAsConstant();
        }
        classScope->insert(property->getId(), property->getPropertyTypeSignature()->getType());
        classScope->insertVariableContext(property->getId(), propertyContext);
    }
    return classScope;
}
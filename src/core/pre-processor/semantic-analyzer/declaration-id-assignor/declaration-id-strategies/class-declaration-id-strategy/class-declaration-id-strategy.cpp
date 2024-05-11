//
// Created by Johny Georges on 2024-05-02.
//

#include "class-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../../shared/utils/to-string/to-string.h"

void ClassDeclarationIdStrategy::assign(ASTNode* node) {
    auto classDeclarationNode = (ASTClassDeclarationNode*)node;
    auto className = _tokenTable->getIdentifier(
            classDeclarationNode->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
    ).value();
    classDeclarationNode->setId(className);
    for (auto classPropertyDeclaration : *classDeclarationNode->getBlock()->getProperties()) {
        classPropertyDeclaration->setId(this->generateClassPropertyDeclarationId(className, classPropertyDeclaration));
    }
    for (auto classMethodDeclaration : *classDeclarationNode->getBlock()->getMethods()) {
        classMethodDeclaration->setId(this->generateClassMethodDeclarationId(className, classMethodDeclaration));
    }
    for (auto constructorDeclaration : *classDeclarationNode->getBlock()->getConstructors()) {
        constructorDeclaration->setId(this->generateClassConstructorDeclarationId(className, constructorDeclaration));
    }

    auto astTraverser = ASTTraverser();
    astTraverser.init(classDeclarationNode);
    auto astNode = astTraverser.next();
    while (astNode) {
        if (astNode.value()->isOneOf({ AST_THIS_EXPRESSION_NODE, AST_THIS_TYPE_NODE })) {
            astNode.value()->setId(classDeclarationNode->getExternalId());
        } else if (astNode.value()->is(AST_THIS_NODE)) {
            astNode.value()->setId(classDeclarationNode->getInternalId());
        }
        astNode = astTraverser.next();
    }
}

std::string ClassDeclarationIdStrategy::generateClassPropertyDeclarationId(std::string className, ASTClassPropertyDeclarationNode* classPropertyDeclaration) {
    return className +
            "_property_" +
            _tokenTable->getIdentifier(
                    classPropertyDeclaration
                    ->getPropertyName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
            ).value();
}

std::string ClassDeclarationIdStrategy::generateClassMethodDeclarationId(std::string className, ASTClassMethodDeclarationNode* classMethodDeclaration) {
    return className +
            "_method_" +
            _tokenTable->getIdentifier(
                classMethodDeclaration
                ->getClassMethodDefinition()
                ->getMethodName()
                ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            ).value();
}

std::string ClassDeclarationIdStrategy::generateClassConstructorDeclarationId(std::string className, ASTClassConstructorDeclarationNode* constructorDeclaration) {
    return className +
        "_constructor_" +
        ToStringUtil::toString(
            constructorDeclaration
            ->getConstructor()
            ->getLexeme()
            ->getLine()
        );
}
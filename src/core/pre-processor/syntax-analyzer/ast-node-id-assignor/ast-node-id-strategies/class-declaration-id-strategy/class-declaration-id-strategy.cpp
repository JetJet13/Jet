//
// Created by Johny Georges on 2024-05-02.
//

#include "class-declaration-id-strategy.h"
#include "../../../../../../shared/utils/to-string/to-string.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-custom-type-node.h"

void ClassDeclarationIdStrategy::assign(ASTNode* node) {
    auto classDeclarationNode = (ASTClassDeclarationNode*)node;
    auto className = classDeclarationNode->getName()->getId();
    classDeclarationNode->setId(className);
    for (auto classPropertyDeclaration : *classDeclarationNode->getBlock()->getProperties()) {
        classPropertyDeclaration->setId(this->generateClassPropertyDeclarationId(className, classPropertyDeclaration));
    }
    for (auto classMethodDeclaration : *classDeclarationNode->getBlock()->getMethods()) {
        classMethodDeclaration->setId(this->generateClassMethodDeclarationId(className, classMethodDeclaration));
    }

    unsigned long constructorIndex = 0;
    for (auto constructorDeclaration : *classDeclarationNode->getBlock()->getConstructors()) {
        constructorDeclaration->setId(this->generateClassConstructorDeclarationId(className, constructorIndex, constructorDeclaration));
        constructorIndex++;
    }

    auto astTraverser = ASTTraverser();
    astTraverser.init(classDeclarationNode);
    auto astNode = astTraverser.next();
    while (astNode) {
        if (astNode.value()->isOneOf({ AST_THIS_EXPRESSION_NODE, AST_THIS_TYPE_NODE, AST_THIS_NODE })) {
            astNode.value()->setId(classDeclarationNode->getId());
        } else if (astNode.value()->is(AST_CUSTOM_TYPE_NODE)) {
            auto customTypeName = _tokenTable->getIdentifier(
                    ((ASTCustomTypeNode *) astNode.value())
                            ->getLexeme()
                            ->getToken()
                            ->getValueId().value()
            );
            if (customTypeName == className) {
                astNode.value()->setId(classDeclarationNode->getId());
            }
        } else if (astNode.value()->is(AST_CLASS_NAME_NODE)) {
            auto nodeClassName = _tokenTable->getIdentifier(
                    ((ASTClassNameNode*)astNode.value())
                            ->getLexeme()
                            ->getToken()
                            ->getValueId().value()
            );
            if (nodeClassName == className) {
                astNode.value()->setId(classDeclarationNode->getId());
            }
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
            );
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
            );
}

std::string ClassDeclarationIdStrategy::generateClassConstructorDeclarationId(std::string className, unsigned long constructorIndex, ASTClassConstructorDeclarationNode* constructorDeclaration) {
    return className + "_constructor_" + ToStringUtil::toString(constructorIndex);
}
//
// Created by Johny Georges on 2024-05-02.
//

#include "class-declaration-id-strategy.h"
#include "../../../../../../shared/utils/to-string/to-string.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-custom-type-node.h"
#include "../../../../../../shared/utils/logger/logger.h"
#include "../../../../../ast-traverser/ast-traverser.h"

void ClassDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto classDeclarationNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(node);
    auto className = classDeclarationNode->getName()->getId();
    classDeclarationNode->setId(className);
    for (auto classPropertyDeclaration : *classDeclarationNode->getBlock()->getProperties()) {
        classPropertyDeclaration->setId(this->generateClassPropertyId(className, classPropertyDeclaration->getPropertyName()));
    }
    for (auto classMethodDeclaration : *classDeclarationNode->getBlock()->getMethods()) {
        classMethodDeclaration->setId(this->generateClassMethodId(className, classMethodDeclaration->getClassMethodDefinition()->getMethodName()));
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
                    std::dynamic_pointer_cast<ASTCustomTypeNode>(astNode.value())
                            ->getLexeme()
                            ->getToken()
                            ->getValueId().value()
            );
            if (customTypeName == className) {
                astNode.value()->setId(classDeclarationNode->getId());
            }
        } else if (astNode.value()->is(AST_CLASS_NAME_NODE)) {
            auto nodeClassName = _tokenTable->getIdentifier(
                    (std::dynamic_pointer_cast<ASTClassNameNode>(astNode.value()))
                            ->getLexeme()
                            ->getToken()
                            ->getValueId().value()
            );
            if (nodeClassName == className) {
                astNode.value()->setId(classDeclarationNode->getId());
            }
        } else if (astNode.value()->is(AST_CLASS_PROPERTY_NAME_NODE)) {
            astNode.value()->setId(
                this->generateClassPropertyId(
                    className,
                    std::dynamic_pointer_cast<ASTClassPropertyNameNode>(astNode.value())
                )
            );
        } else if (astNode.value()->is(AST_CLASS_METHOD_NAME_NODE)) {
            astNode.value()->setId(
                this->generateClassMethodId(
                    className,
                    std::dynamic_pointer_cast<ASTClassMethodNameNode>(astNode.value())
                )
            );
        } else if (astNode.value()->is(AST_CLASS_METHOD_CALL_NODE)) {
            astNode.value()->setId(
                this->generateClassMethodId(
                        className,
                        std::dynamic_pointer_cast<ASTClassMethodCallNode>(astNode.value())
                )
            );
        }
        astNode = astTraverser.next();
    }
}

std::string ClassDeclarationIdStrategy::generateClassPropertyId(std::string className, std::shared_ptr<ASTClassPropertyNameNode> classPropertyName) {
    return className +
            "." +
            _tokenTable->getIdentifier(
                    classPropertyName
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
            );
}

std::string ClassDeclarationIdStrategy::generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodNameNode> classMethodName) {
    return this->generateClassMethodId(className, classMethodName->getLexeme());
}

std::string ClassDeclarationIdStrategy::generateClassMethodId(std::string className, std::shared_ptr<ASTClassMethodCallNode> classMethodCall) {
    return this->generateClassMethodId(className, classMethodCall->getLexeme());
}

std::string ClassDeclarationIdStrategy::generateClassMethodId(std::string className, Lexeme* lexeme) {
    return className +
           "." +
           _tokenTable->getIdentifier(
                   lexeme->getToken()
                   ->getValueId()
                   .value()
           );
}

std::string ClassDeclarationIdStrategy::generateClassConstructorDeclarationId(std::string className, unsigned long constructorIndex, std::shared_ptr<ASTClassConstructorDeclarationNode> constructorDeclaration) {
    return className + "_constructor_" + ToStringUtil::toString(constructorIndex);
}
//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../../shared/utils/logger/logger.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"

ClassTypeSignature* ClassTypeSignatureStrategy::create(ASTClassDeclarationNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    this->createPropertyTypeSignatures(node, classTypeSignature, strategyMap);
    this->createConstructorTypeSignatures(node, classTypeSignature, strategyMap);
    this->createMethodTypeSignatures(node, classTypeSignature, strategyMap);
    return classTypeSignature;
}

void ClassTypeSignatureStrategy::createConstructorTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        auto constructorTypeSignature = strategyMap->getTypeSignatureForClassConstructor(constructor);
        for (int i = 0; i < constructor->getParameters()->numParameters(); ++i) {
            auto parameter = constructor->getParameters()->getParameters().at(i);
            if (parameter->getType()->getType()->getId() == node->getId()) {
                constructorTypeSignature
                ->getParameterList()
                ->getParameters()
                ->at(i)
                ->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }
        classTypeSignature->addConstructor(
            constructor->getId(),
            constructorTypeSignature
        );
    }
}

void ClassTypeSignatureStrategy::createPropertyTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        auto propertyTypeSignature = strategyMap->getTypeSignatureForClassProperty(property);
        if (property->getPropertyInit()->getType() &&
            property->getPropertyInit()->getType().value()->getType()->getId() == node->getId()) {
            propertyTypeSignature->setType(new ClassInstanceTypeSignature(classTypeSignature));
        }

        if (property->getInitializer() && property->getInitializer().value()->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
            auto newClassInstanceExpression = (ASTNewClassInstanceExpressionNode*)property->getInitializer().value();
            if (newClassInstanceExpression->getClassName()->getId() == node->getId()) {
                propertyTypeSignature->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }

        classTypeSignature->addProperty(
                property->getId(),
                propertyTypeSignature
        );
    }
}

void ClassTypeSignatureStrategy::createMethodTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        auto methodTypeSignature = strategyMap->getTypeSignatureForClassMethod(method);
        for (int i = 0; i < method->getParameters()->numParameters(); ++i) {
            auto parameter = method->getParameters()->getParameters().at(i);
            if (parameter->getType()->getType()->getId() == node->getId()) {
                methodTypeSignature
                ->getParameters()
                ->getParameters()
                ->at(i)
                ->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }
        if (methodTypeSignature &&
            method->getReturnType() &&
            method->getReturnType().value()->getType()->getId() == node->getId()) {
            methodTypeSignature->setReturnType(new ClassInstanceTypeSignature(classTypeSignature));
        }
        classTypeSignature->addMethod(
                method->getId(),
                methodTypeSignature
        );
    }
}